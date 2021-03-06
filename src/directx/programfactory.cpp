/*
 * This file is part of `et engine`
 * Copyright 2009-2015 by Sergey Reznik
 * Please, modify content only if you know what are you doing.
 *
 */

#include <et/app/application.h>
#include <et/rendering/rendercontext.h>
#include <et/rendering/programfactory.h>

using namespace et;

class et::ProgramFactoryPrivate 
{
public:
	struct Loader : public ObjectLoader
	{
		ProgramFactory* owner = nullptr;

		Loader(ProgramFactory* aOwner) :
			owner(aOwner) { }

		void reloadObject(LoadableObject::Pointer o, ObjectsCache& c)
			{ owner->reloadObject(o, c); }
	};

	IntrusivePtr<Loader> loader;

	ProgramFactoryPrivate(ProgramFactory* owner) : 
		loader(sharedObjectFactory().createObject<Loader>(owner)) { }
};

StringList parseDefinesString(std::string defines, std::string separators = ",; \t");

ProgramFactory::ProgramFactory(RenderContext* rc) : APIObjectFactory(rc)
{
	ET_PIMPL_INIT(ProgramFactory, this)
}

ProgramFactory::~ProgramFactory()
{
	ET_PIMPL_FINALIZE(ProgramFactory)
}

StringList ProgramFactory::loadProgramSources(const std::string& file, std::string& vertex_shader,
	std::string& geom_shader, std::string& frag_shader, const StringList& defines)
{
	StringList sources;
	
	std::string filename = application().resolveFileName(file);
	if (!fileExists(filename))
	{
		log::error("Unable to find file: %s", file.c_str());
		return sources;
	}
	
	StringList resultDefines = defines;
	std::string vertex_source;
	std::string geometry_source;
	std::string fragment_source;
	std::string s;
	
	InputStream progFile(filename, StreamMode_Binary);
	while (!(progFile.stream().eof() || progFile.stream().fail()))
	{
		getline(progFile.stream(), s);
		trim(s);
		
		std::string id = s.substr(0, s.find(':'));
		trim(id);
		lowercase(id);
		
		if (id == "vs")
			vertex_source = s.substr(s.find_first_of(':') + 1);
		
		if (id == "gs")
			geometry_source = s.substr(s.find_first_of(':') + 1);
		
		if (id == "fs")
			fragment_source = s.substr(s.find_first_of(':') + 1);
		
		if (id == "defines")
		{
			StringList aDefines = parseDefinesString(s.substr(s.find_first_of(':') + 1));
			resultDefines.insert(resultDefines.end(), aDefines.begin(), aDefines.end());
		}
	}
	
	normalizeFilePath(trim(vertex_source));
	normalizeFilePath(trim(geometry_source));
	normalizeFilePath(trim(fragment_source));
	
	std::string programFolder = getFilePath(filename);
	std::string fName = programFolder + vertex_source;
	
	if (!fileExists(fName))
		fName = application().resolveFileName(fName);
	
	if (!fileExists(fName))
		fName = application().resolveFileName(vertex_source);
	
	if (fileExists(fName))
	{
		sources.push_back(fName);
		vertex_shader = loadTextFile(fName);
		ET_ASSERT((vertex_shader.size() > 1) && "Vertex shader source should not be empty");
	}
	
	if (!geometry_source.empty())
	{
		fName = programFolder + geometry_source;
		if (!fileExists(fName))
			fName = application().resolveFileName(fName);
		
		if (!fileExists(fName))
			fName = application().resolveFileName(geometry_source);
		
		if (fileExists(fName))
		{
			geom_shader = loadTextFile(fName);
			sources.push_back(fName);
		}
	}
	
	fName = programFolder + fragment_source;
	
	if (!fileExists(fName))
		fName = application().resolveFileName(fName);
	
	if (!fileExists(fName))
		fName = application().resolveFileName(fragment_source);
	
	if (fileExists(fName))
	{
		sources.push_back(fName);
		frag_shader = loadTextFile(fName);
		ET_ASSERT((frag_shader.size() > 1) && "Fragment shader source should not be empty");
	}
	
	return sources;
}

Program::Pointer ProgramFactory::loadProgram(const std::string& file, ObjectsCache& cache,
	const StringList& defines)
{
	auto cachedPrograms = cache.findObjects(file);
	for (Program::Pointer cached : cachedPrograms)
	{
		if (cached.valid())
		{
			if (cached->defines().size() == defines.size())
			{
				bool same = true;
				for (auto& inDefine : defines)
				{
					for (auto& cDefine : cached->defines())
					{
						if (inDefine != cDefine)
						{
							same = false;
							break;
						}
						
						if (!same)
							break;
					}
				}
				if (same)
					return cached;
			}
		}
	}
	
	std::string vertex_shader;
	std::string geom_shader;
	std::string frag_shader;

	StringList sourceFiles = loadProgramSources(file, vertex_shader, geom_shader, frag_shader);
	
	if (sourceFiles.empty())
		return Program::Pointer::create(renderContext());
	
	std::string workFolder = getFilePath(file);
	
	parseSourceCode(ShaderType_Vertex, vertex_shader, defines, workFolder);
	parseSourceCode(ShaderType_Geometry, geom_shader, defines, workFolder);
	parseSourceCode(ShaderType_Fragment, frag_shader, defines, workFolder);
	
	Program::Pointer program = Program::Pointer::create(renderContext(), vertex_shader, geom_shader,
		frag_shader, getFileName(file), file, defines);
	
	for (auto& s : sourceFiles)
		program->addOrigin(s);
	
	cache.manage(program, _private->loader);
	return program;
}

Program::Pointer ProgramFactory::loadProgram(const std::string& file, ObjectsCache& cache, const std::string& defines)
{
	return loadProgram(application().resolveFileName(file), cache, parseDefinesString(defines));
}

Program::Pointer ProgramFactory::genProgram(const std::string& name, const std::string& vertexshader,
	const std::string& geometryshader, const std::string& fragmentshader, const StringList& defines,
	const std::string& workFolder)
{
	std::string vs = vertexshader;
	std::string gs = geometryshader;
	std::string fs = fragmentshader;
	
	parseSourceCode(ShaderType_Vertex, vs, defines, workFolder);
	parseSourceCode(ShaderType_Geometry, gs, defines, workFolder);
	parseSourceCode(ShaderType_Fragment, fs, defines, workFolder);
	
	return Program::Pointer::create(renderContext(), vs, gs, fs, name, name, defines);
}

Program ::Pointer ProgramFactory::genProgram(const std::string& name, const std::string& vertexshader,
	const std::string& fragmentshader, const StringList& defines, const std::string& workFolder)
{
	std::string vs = vertexshader;
	std::string fs = fragmentshader;
	
	parseSourceCode(ShaderType_Vertex, vs, defines, workFolder);
	parseSourceCode(ShaderType_Fragment, fs, defines, workFolder);
	
	return Program::Pointer::create(renderContext(), vs, emptyString, fs, name, name, defines);
}

void ProgramFactory::parseSourceCode(ShaderType type, std::string& source, const StringList& defines,
	const std::string& workFolder)
{
	if (source.empty()) return;
	
	std::string header = _commonHeader;
	
	if (type == ShaderType_Vertex)
		header += _vertShaderHeader;
	else if (type == ShaderType_Fragment)
		header += _fragShaderHeader;

	for (const auto& i : defines)
		header += "\n#define " + i;

	source = header + "\n" + source;

	std::string::size_type ip = source.find("#include");

	bool hasIncludes = ip != std::string::npos;
	while (hasIncludes)
	{
		while (ip != std::string::npos)
		{
			std::string before = source.substr(0, ip);
			
			source.erase(0, before.size());
			std::string ifname = source.substr(0, source.find_first_of(char(10)));
			source.erase(0, ifname.size());
			std::string after = source.substr();
			
			if (ifname.find_first_of('"') != std::string::npos)
			{
				ifname.erase(0, ifname.find_first_of('"') + 1);
				ifname.erase(ifname.find_last_of('"'));
			}
			else 
			{
				ifname.erase(0, ifname.find_first_of('<') + 1);
				ifname.erase(ifname.find_last_of('>'));
			}
			
			std::string include = "";
			
			std::string baseName = removeUpDir(workFolder + ifname);
			while (baseName.find("..") != std::string::npos)
				baseName = removeUpDir(baseName);
			
			if (fileExists(baseName))
			{
				include = loadTextFile(baseName);
			}
			else
			{
				log::error("failed to include %s, starting from folder %s", ifname.c_str(), workFolder.c_str());
			}
			
			source = before + include + after;
			ip = source.find("#include");
		}
		
		hasIncludes = ip != std::string::npos;
	}
}


void ProgramFactory::reloadObject(LoadableObject::Pointer obj, ObjectsCache&)
{
	std::string vertex_shader;
	std::string geom_shader;
	std::string frag_shader;
	
	StringList sourceFiles = loadProgramSources(obj->origin(), vertex_shader, geom_shader, frag_shader);
	if (sourceFiles.empty()) return;
	
	// TODO: handle defines
	std::string workFolder = getFilePath(obj->origin());
	parseSourceCode(ShaderType_Vertex, vertex_shader, StringList(), workFolder);
	parseSourceCode(ShaderType_Geometry, geom_shader, StringList(), workFolder);
	parseSourceCode(ShaderType_Fragment, frag_shader, StringList(), workFolder);
	
	Program::Pointer(obj)->buildProgram(vertex_shader, geom_shader, frag_shader);
}

StringList parseDefinesString(std::string defines, std::string separators)
{
	StringList result;
	
	if (separators.length() == 0)
		separators = ",; \t";

	while (defines.length() > 0)
	{
		std::string::size_type separator_pos = std::string::npos;

		for (auto& s_i : separators)
		{
			std::string::size_type s = defines.find_first_of(s_i);
			if (s != std::string::npos)
			{
				separator_pos = s;
				break;
			}
		}

		if (separator_pos == std::string::npos)
		{
			result.push_back(defines);
			break;
		}
		else
		{
			std::string define = defines.substr(0, separator_pos);
			defines.erase(0, separator_pos + 1);

			if (define.size() > 0)
				result.push_back(define);
		}
	}
	
	return result;
}
