/*
* This file is part of `et engine`
* Copyright 2009-2013 by Sergey Reznik
* Please, do not modify content without approval.
*
*/

#include <Windows.h>
#include <Psapi.h>
#include <et/core/et.h>
#include <et/core/memory.h>

using namespace et;

size_t et::memoryUsage()
{
	PROCESS_MEMORY_COUNTERS pmc = { sizeof(PROCESS_MEMORY_COUNTERS) };
	GetProcessMemoryInfo(GetCurrentProcess(), &pmc, pmc.cb);
	return pmc.WorkingSetSize;
}

size_t et::availableMemory()
{
	ET_FAIL("Not implemented.");
	return 0;
}

void* et::allocateVirtualMemory(size_t size)
{
	ET_FAIL("Not implemented.");
	return nullptr;
}

void et::deallocateVirtualMemory(void* ptr, size_t size)
{
	ET_FAIL("Not implemented.");
}
