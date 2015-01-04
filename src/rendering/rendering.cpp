/*
 * This file is part of `et engine`
 * Copyright 2009-2015 by Sergey Reznik
 * Please, modify content only if you know what are you doing.
 *
 */

#include <et/rendering/rendering.h>

namespace et
{

	const std::string vertexAttributeUsageNames[VertexAttributeUsage_max] =
	{ 
		"Vertex", "Normal", "Color", "Tangent", "Binormal",
		"TexCoord0", "TexCoord1", "TexCoord2", "TexCoord3",
		"SmoothingGroup", "gl_InstanceID", "gl_InstanceIDEXT"
	};

	const uint32_t vertexAttributeUsageMasks[VertexAttributeUsage_max] =
		{ 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0x0 };

	VertexAttributeUsage stringToVertexAttribute(const std::string& s)
	{
		for (uint32_t i = 0, e = VertexAttributeUsage_max; i < e; ++i)
		{
			if (s == vertexAttributeUsageNames[i])
				return static_cast<VertexAttributeUsage>(i);
		}
		
		ET_FAIL_FMT("Unknown vertex attribute usage: %s", s.c_str());
		return VertexAttributeUsage::Position;
	}

	std::string vertexAttributeToString(VertexAttributeUsage va)
	{
		return (va < VertexAttributeUsage::max) ? vertexAttributeUsageNames[static_cast<uint32_t>(va)] : emptyString;
	}

	uint32_t vertexAttributeTypeComponents(VertexAttributeType t)
	{
		ET_ASSERT(t < VertexAttributeType::max)
		
		static const uint32_t values[VertexAttributeType_max] =
		{
			1,  // Float,
			2,  // Vec2,
			3,  // Vec3,
			4,  // Vec4,
			9,  // Mat3,
			16, // Mat4,
			1,  // Int,
		};
		return values[static_cast<uint32_t>(t)];
	}

	DataType vertexAttributeTypeDataType(VertexAttributeType t)
	{
		ET_ASSERT(t < VertexAttributeType::max)
		
		static const DataType values[VertexAttributeType_max] =
		{
			DataType::Float, // Float,
			DataType::Float, // Vec2,
			DataType::Float, // Vec3,
			DataType::Float, // Vec4,
			DataType::Float, // Mat3,
			DataType::Float, // Mat4,
			DataType::Int, // Int,
		};
		return values[int32_t(t)];
	}

	uint32_t vertexAttributeTypeSize(VertexAttributeType t)
	{
		return vertexAttributeTypeComponents(t) * ((t == VertexAttributeType::Int) ? sizeof(int) : sizeof(float));
	}

	uint32_t vertexAttributeUsageMask(VertexAttributeUsage u)
	{
		ET_ASSERT(u < VertexAttributeUsage::max)
		return vertexAttributeUsageMasks[static_cast<uint32_t>(u)];
	}
	
	uint32_t bitsPerPixelForTextureFormat(TextureFormat format, DataType type)
	{
		switch (format)
		{
			case TextureFormat::R8:
				return 8;
				
			case TextureFormat::R16:
			case TextureFormat::R16F:
			case TextureFormat::RG8:
			case TextureFormat::Depth16:
				return 16;
				
			case TextureFormat::RGB8:
			case TextureFormat::Depth24:
				return 24;
				
			case TextureFormat::RG16:
			case TextureFormat::RG16F:
			case TextureFormat::RGBA8:
			case TextureFormat::Depth32:
				return 32;
				
			case TextureFormat::RGB16:
			case TextureFormat::RGB16F:
				return 48;
				
			case TextureFormat::RGBA16:
			case TextureFormat::RGBA16F:
				return 64;
				
			case TextureFormat::RGB32F:
				return 96;
				
			case TextureFormat::RGBA32F:
				return 128;
				
			case TextureFormat::RG:
			case TextureFormat::R:
			case TextureFormat::Depth:
				return bitsPerPixelForType(type);
				
			case TextureFormat::RGB:
			case TextureFormat::BGR:
			{
				switch (type)
				{
					case DataType::UnsignedShort_565:
						return 16;
						
					default:
						return 3 * bitsPerPixelForType(type);
				}
			}
				
			case TextureFormat::RGBA:
			case TextureFormat::BGRA:
			{
				switch (type)
				{
					case DataType::UnsignedShort_4444:
					case DataType::UnsignedShort_5551:
						return 16;
						
					default:
						return 4 * bitsPerPixelForType(type);
				}
			}
				
			default:
			{
				ET_FAIL_FMT("Not yet implemented for this format: %u, with data type: %u",
					static_cast<uint32_t>(format), static_cast<uint32_t>(type));
				return 0;
			}
		}
	}
	
	uint32_t bitsPerPixelForType(DataType type)
	{
		switch (type)
		{
			case DataType::Char:
			case DataType::UnsignedChar:
				return 8;
				
			case DataType::Short:
			case DataType::UnsignedShort:
			case DataType::UnsignedShort_4444:
			case DataType::UnsignedShort_5551:
			case DataType::UnsignedShort_565:
				return 16;
				
			case DataType::Int:
			case DataType::UnsignedInt:
				return 32;
				
			case DataType::Half:
				return 16;
				
			case DataType::Float:
				return 32;
				
			case DataType::Double:
				return 64;
				
			default:
			{
				ET_FAIL_FMT("Unknown data type: %u", static_cast<uint32_t>(type));
				return 0;
			}
		}
	}
	
	uint32_t channelsForTextureFormat(TextureFormat internalFormat)
	{
		switch (internalFormat)
		{
			case TextureFormat::Depth:
			case TextureFormat::Depth16:
			case TextureFormat::Depth24:
			case TextureFormat::Depth32:
			case TextureFormat::Depth32F:
			case TextureFormat::R:
			case TextureFormat::R8:
			case TextureFormat::R16:
			case TextureFormat::R16F:
			case TextureFormat::R32F:
				return 1;
				
			case TextureFormat::RG:
			case TextureFormat::RG8:
			case TextureFormat::RG16:
			case TextureFormat::RG16F:
			case TextureFormat::RG32F:
			case TextureFormat::RGTC2:
				return 2;
				
			case TextureFormat::RGB:
			case TextureFormat::BGR:
			case TextureFormat::RGB8:
			case TextureFormat::RGB16:
			case TextureFormat::RGB16F:
			case TextureFormat::RGB32F:
			case TextureFormat::DXT1_RGB:
				return 3;
				
			case TextureFormat::RGBA:
			case TextureFormat::BGRA:
			case TextureFormat::RGBA8:
			case TextureFormat::RGBA16:
			case TextureFormat::RGBA16F:
			case TextureFormat::RGBA32F:
			case TextureFormat::DXT1_RGBA:
			case TextureFormat::DXT3:
			case TextureFormat::DXT5:
				return 4;
				
			default:
			{
				ET_FAIL_FMT("Channels not defined for format %u", static_cast<uint32_t>(internalFormat));
				return 0;
			}
		}
	}
}
