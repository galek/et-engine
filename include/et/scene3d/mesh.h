/*
 * This file is part of `et engine`
 * Copyright 2009-2015 by Sergey Reznik
 * Please, modify content only if you know what are you doing.
 *
 */

#pragma once

#include <et/rendering/vertexarrayobject.h>
#include <et/scene3d/baseelement.h>

namespace et
{
	namespace s3d
	{
		class Mesh : public RenderableElement
		{
		public:
			ET_DECLARE_POINTER(Mesh)
			
			typedef std::map<size_t, Pointer> LodMap;
			static const std::string defaultMeshName;

		public:
			Mesh(const std::string& name = defaultMeshName, Element* parent = 0);

			Mesh(const std::string& name, const VertexArrayObject& ib, const Material::Pointer& material,
				uint32_t startIndex, size_t numIndexes, Element* parent = 0);

			ElementType type() const 
				{ return ElementType_Mesh; }

			Mesh* duplicate();

			VertexArrayObject& vertexArrayObject();
			const VertexArrayObject& vertexArrayObject() const;

			VertexBuffer& vertexBuffer();
			const VertexBuffer& vertexBuffer() const;

			IndexBuffer& indexBuffer();
			const IndexBuffer& indexBuffer() const;

			uint32_t startIndex() const;
			void setStartIndex(uint32_t index);
			
			size_t numIndexes() const;
			virtual void setNumIndexes(size_t num);

			void setVertexBuffer(VertexBuffer vb);
			void setIndexBuffer(IndexBuffer ib);
			void setVertexArrayObject(VertexArrayObject vao);

			void serialize(std::ostream& stream, SceneVersion version);
			void deserialize(std::istream& stream, ElementFactory* factory, SceneVersion version);

			void cleanupLodChildren();
			void attachLod(size_t level, Mesh::Pointer mesh);

			void setLod(size_t level);
			
			const std::string& vaoName() const
				{ return _vaoName; }
			
			const std::string& vbName() const
				{ return _vbName; }
			
			const std::string& ibName() const
				{ return _ibName; }

		private:
			Mesh* currentLod();
			const Mesh* currentLod() const;

		private:
			VertexArrayObject _vao;
			LodMap _lods;
			uint32_t _startIndex;
			size_t _numIndexes;
			size_t _selectedLod;
			std::string _vaoName;
			std::string _vbName;
			std::string _ibName;
		};
	}
}
