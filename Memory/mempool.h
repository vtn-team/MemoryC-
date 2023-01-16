#pragma once

#include <iostream>
#include <new>
#include <assert.h>

class MemoryPool
{
	int _size;
	int _unitSize;
	int _lastPoint;
	char* _pool;
	bool* _use;

	MemoryPool();
	void* readFreeMem();
public:
	~MemoryPool();

	static MemoryPool* create(int size, int unitSize);

	template<typename T>
	T* New()
	{
		int s = sizeof(T);
		assert(s <= _unitSize);
		void* memPoint = readFreeMem();
		assert(memPoint);
		T* ret = new(memPoint) T();
		return ret;
	}

	template<typename T>
	T* NewArray(size_t n)
	{
		std::cout << typeid(T).name();
		int s = sizeof(T);
		assert(s <= _unitSize);
		void* memPoint = readFreeMem();
		assert(memPoint);
		T* ret = new(memPoint) T();
		return ret;
	}

	char* GetData(int index);
	void Free(void* ptr);
};

class AllocatorMemory {
	static MemoryPool* _pool;
	AllocatorMemory() {}
public:
	static void setPool(MemoryPool* p)
	{
		_pool = p;
	}
	static MemoryPool* getPool()
	{
		return _pool;
	}
};

template <class T>
class  Allocator {
	MemoryPool* _pool;

public:
	using value_type = T;

	Allocator() {
		_pool = AllocatorMemory::getPool();
	}
    template <class U>
    Allocator(const Allocator<U>&)
	{
		_pool = AllocatorMemory::getPool();;
	}

    T* allocate(std::size_t n)
    {
        return _pool->NewArray<T>(n);
    }

    void deallocate(T* p, std::size_t n)
    {
		_pool->Free(p);
    }
};

// ”äŠr‰‰ŽZŽq
template <class T, class U>
bool operator==(const Allocator<T>&, const Allocator<U>&)
{
	return true;
}

template <class T, class U>
bool operator!=(const Allocator<T>&, const Allocator<U>&)
{
	return false;
}