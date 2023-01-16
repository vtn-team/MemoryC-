#pragma once

void* operator new(size_t size, const char* file, const int line);
void operator delete(void*);

#define NEW new( __FILE__, __LINE__)

void leakdump();