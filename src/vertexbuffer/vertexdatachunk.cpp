/*
 * This file is part of `et engine`
 * Copyright 2009-2015 by Sergey Reznik
 * Please, modify content only if you know what are you doing.
 *
 */

#include <et/core/serialization.h>
#include <et/vertexbuffer/vertexdatachunk.h>

namespace et
{
	VertexAttributeType openglTypeToVertexAttributeType(uint32_t);
}

using namespace et;

VertexDataChunkData::VertexDataChunkData(VertexAttributeUsage aUsage, VertexAttributeType aType, size_t aSize) :
	_usage(aUsage), _type(aType)
{
	ET_ASSERT(_type < VertexAttributeType::max);
	
	_data.resize(vertexAttributeTypeSize(_type) * aSize);
	_data.fill(0);
}

VertexDataChunkData::VertexDataChunkData(std::istream& stream)
{
	_usage = static_cast<VertexAttributeUsage>(deserializeInt(stream));
	_type = static_cast<VertexAttributeType>(deserializeInt(stream));
	_data.resize(deserializeUInt(stream));
	_data.setOffset(deserializeUInt(stream));
	
	stream.read(_data.binary(), static_cast<std::streamsize>(_data.dataSize()));
	
	/*
	 * Support legacy values
	 */
	if (_type >= VertexAttributeType::max)
		_type = openglTypeToVertexAttributeType(static_cast<uint32_t>(_type));
}

void VertexDataChunkData::serialize(std::ostream& stream)
{
	serializeInt(stream, static_cast<uint32_t>(_usage));
	serializeInt(stream, static_cast<uint32_t>(_type));
	serializeInt(stream, static_cast<int>(_data.dataSize()));
	serializeInt(stream, _data.lastElementIndex());
	stream.write(_data.binary(), static_cast<std::streamsize>(_data.dataSize()));
}

void VertexDataChunkData::resize(size_t sz)
{
	_data.resize(typeSize() * sz);
}

void VertexDataChunkData::fitToSize(size_t count)
{
	if (_data.dataSize() < typeSize() * count)
		resize(count);
}

void VertexDataChunkData::copyTo(VertexDataChunkData& c) const
{
	c._usage = _usage;
	c._type = _type;
	c._data = _data;
}
