
#include <iostream>
#include <new>
#include <map>
#include "operator.h"

struct MemInfo
{
	char File[256];
	int Line;
};
std::map<void*, MemInfo> gMemInfo;

void* operator new(size_t size, const char* file, const int line)
{
	void* ptr = std::malloc(size);
	MemInfo info;
	info.Line = line;
	snprintf(info.File, 256, file);
	gMemInfo.emplace(ptr, info);
	return ptr;
}

void operator delete(void* p)
{
	/*
	auto itr = gMemInfo.find(p);
	if (itr != gMemInfo.end())
	{
		gMemInfo.erase(p);
	}
	*/
	free(p);
}

void leakdump()
{
	for (auto log : gMemInfo)
	{
		printf("%p: %s(%d)\n", log.first, log.second.File, log.second.Line);
	}
}