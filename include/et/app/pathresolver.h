/*
 * This file is part of `et engine`
 * Copyright 2009-2013 by Sergey Reznik
 * Please, do not modify content without approval.
 *
 */

#pragma once

#include <set>
#include <deque>
#include <et/core/et.h>

namespace et
{
	class RenderContext;
	
	class PathResolver : public Shared
	{
	public:
		ET_DECLARE_POINTER(PathResolver)
		
	public:
		virtual std::string resolveFilePath(const std::string&) = 0;
		virtual std::string resolveFolderPath(const std::string&) = 0;
		virtual std::set<std::string> resolveFolderPaths(const std::string&) = 0;
		
		virtual ~PathResolver() { }
	};
	
	class StandardPathResolver : PathResolver
	{
	public:
		ET_DECLARE_POINTER(StandardPathResolver)
		
	public:
		void setRenderContext(RenderContext*);
		
		std::string resolveFilePath(const std::string&);
		std::string resolveFolderPath(const std::string&);
		std::set<std::string> resolveFolderPaths(const std::string&);
		
		void pushSearchPath(const std::string& path);
		void pushSearchPaths(const std::set<std::string>& path);
		void pushRelativeSearchPath(const std::string& path);
		
		void popSearchPaths(size_t = 1);
		
	private:
		void validateCaches();
		
	private:
		RenderContext* _rc = nullptr;
		std::deque<std::string> _searchPath;
		
		std::string _cachedLang;
		std::string _cachedSubLang;
		std::string _cachedLanguage;
		std::string _cachedScreenScale;
		std::string _baseFolder;
		
		size_t _cachedLocale = 0;
		size_t _cachedScreenScaleFactor = 0;
	};
}
