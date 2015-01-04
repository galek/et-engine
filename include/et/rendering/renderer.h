/*
 * This file is part of `et engine`
 * Copyright 2009-2015 by Sergey Reznik
 * Please, modify content only if you know what are you doing.
 *
 */

#pragma once

#include <et/rendering/renderstate.h>

namespace et
{
	class RenderContext;
	class Renderer : public Shared
	{
	public:
		ET_DECLARE_POINTER(Renderer)
		
	public: 
		Renderer(RenderContext*);

		void clear(bool color = true, bool depth = true);

		void fullscreenPass();
		void renderFullscreenTexture(const Texture::Pointer&);
		void renderFullscreenTexture(const Texture::Pointer&, const vec2& scale);

		void renderFullscreenDepthTexture(const Texture::Pointer&, float factor);

		void renderTexture(const Texture::Pointer&, const vec2& position, const vec2& size);
		void renderTexture(const Texture::Pointer&, const vec2i& position, const vec2i& size = vec2i(-1));

		void drawElements(const IndexBuffer& ib, size_t first, size_t count);
		void drawElements(PrimitiveType primitiveType, const IndexBuffer& ib, size_t first, size_t count);
		void drawAllElements(const IndexBuffer& ib);

		void drawElementsInstanced(const IndexBuffer& ib, size_t first, size_t count, size_t instances);
		void drawElementsBaseIndex(const VertexArrayObject& vao, int base, size_t first, size_t count);
		
		BinaryDataStorage readFramebufferData(const vec2i&, TextureFormat, DataType);
		void readFramebufferData(const vec2i&, TextureFormat, DataType, BinaryDataStorage&);

		vec2 currentViewportCoordinatesToScene(const vec2i& coord);
		vec2 currentViewportSizeToScene(const vec2i& size);

		ET_DECLARE_PROPERTY_GET_COPY_SET_COPY(uint32_t, defaultTextureBindingUnit, setDefaultTextureBindingUnit)
		
	private:
		Renderer& operator = (const Renderer&)
			{ return *this; }

	private:
		RenderContext* _rc;
		ObjectsCache _sharedCache;
		VertexArrayObject _fullscreenQuadVao;

		Program::Pointer _fullscreenProgram;
		Program::Pointer _fullscreenDepthProgram;
		Program::Pointer _fullscreenScaledProgram;
		Program::Pointer _scaledProgram;

		Program::Uniform _scaledProgram_PSUniform;
		Program::Uniform _fullScreenScaledProgram_PSUniform;
		Program::Uniform _fullScreenDepthProgram_FactorUniform;
	};
}
