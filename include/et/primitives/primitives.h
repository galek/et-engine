/*
 * This file is part of `et engine`
 * Copyright 2009-2014 by Sergey Reznik
 * Please, do not modify content without approval.
 *
 */

#pragma once

#include <et/core/containers.h>
#include <et/vertexbuffer/indexarray.h>
#include <et/vertexbuffer/vertexarray.h>

namespace et
{
	namespace primitives
	{
		size_t primitiveCountForIndexCount(size_t numIndexes, PrimitiveType geometryType);
		
		uint32_t indexCountForRegularMesh(const vec2i& meshSize, PrimitiveType geometryType);

		/*
		 * Index array stuff
		 */
		uint32_t buildTrianglesIndexes(IndexArray& buffer, const vec2i& dim,
			uint32_t vertexOffset, uint32_t indexOffset);
		uint32_t buildTriangleStripIndexes(IndexArray& buffer, const vec2i& dim,
			uint32_t vertexOffset, uint32_t indexOffset);
		uint32_t buildTrianglesIndexes(IndexArray::Pointer buffer, const vec2i& dim,
			uint32_t vertexOffset, uint32_t indexOffset);
		uint32_t buildTriangleStripIndexes(IndexArray::Pointer buffer, const vec2i& dim,
			uint32_t vertexOffset, uint32_t indexOffset);

		void createPhotonMap(VertexArray::Pointer data, const vec2i& density);

		void createSphere(VertexArray::Pointer data, float radius, const vec2i& density,
			const vec3& center = vec3(0.0f), const vec2& hemiSphere = vec2(1.0f));
		
		void createCylinder(VertexArray::Pointer data, float radius, float height, const vec2i& density,
			const vec3& center = vec3(0.0f));
		
		void createTorus(VertexArray::Pointer data, float centralRadius, float sizeRadius,
			const vec2i& density);
		
		void createSquarePlane(VertexArray::Pointer data, const vec3& normal, const vec2& size,
			const vec2i& density, const vec3& center = vec3(0.0f), const vec2& texCoordScale = vec2(1.0f),
			const vec2& texCoordOffset = vec2(0.0f));

		IndexArray::Pointer createCirclePlane(VertexArray::Pointer data, const vec3& normal, float radius,
			size_t density, const vec3& center = vec3(0.0f), const vec2& texCoordScale = vec2(1.0f),
			const vec2& texCoordOffset = vec2(0.0f));
		
		void calculateNormals(VertexArray::Pointer data, const IndexArray::Pointer& buffer,
			size_t first, size_t last);
		
		void calculateTangents(VertexArray::Pointer data, const IndexArray::Pointer& buffer,
			uint32_t first, uint32_t last);
		
		void smoothTangents(VertexArray::Pointer data, const IndexArray::Pointer& buffer,
			uint32_t first, uint32_t last);
		
		void createCube(VertexArray::Pointer data, float radius, const vec3& center = vec3(0.0f));
		void createOctahedron(VertexArray::Pointer data, float radius);
		void createDodecahedron(VertexArray::Pointer data, float radius);
		void createIcosahedron(VertexArray::Pointer data, float radius, bool top = true, bool middle = true, bool bottom = true);
		
		void tesselateTriangles(VertexArray::Pointer data, const vec3& aspect = vec3(0.5f));
		void tesselateTriangles(VertexArray::Pointer data, IndexArray::Pointer indexArray, const vec3& aspect = vec3(0.5f));
		
		VertexArray::Pointer buildLinearIndexArray(VertexArray::Pointer data, IndexArray::Pointer indexArray);
		
		VertexArray::Pointer linearizeTrianglesIndexArray(VertexArray::Pointer data, IndexArray::Pointer indexArray);
		
		uint64_t vector3Hash(const vec3&);
	}
}
