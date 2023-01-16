
#include <cstring>
#include "mempool.h"

MemoryPool* AllocatorMemory::_pool = NULL;

MemoryPool::MemoryPool()
{
	_lastPoint = 0;
	_pool = NULL;
	_size = 0;
	_unitSize = 0;
	_use = NULL;
}

MemoryPool::~MemoryPool()
{
	if (_pool)
	{
		std::free(_pool);
		delete[] _use;
	}
}

void* MemoryPool::readFreeMem()
{
	void* ret = NULL;
	for (int i = 0; i < _size; ++i)
	{
		int index = (_lastPoint + i) % _size;
		if (_use[index]) continue;

		_use[index] = true;
		ret = _pool + (index * _unitSize);
		_lastPoint = index + 1;
		break;
	}
	return ret;
}

MemoryPool* MemoryPool::create(int size, int unitSize)
{
	MemoryPool* pool = new MemoryPool();
	pool->_size = size;
	pool->_unitSize = unitSize;
	pool->_pool = (char*)std::malloc(size * unitSize);
	pool->_use = new bool[size];
	std::memset(pool->_use, 0x0, size);
	return pool;
}

char* MemoryPool::GetData(int index)
{
	return (_pool + index);
}

void MemoryPool::Free(void* ptr)
{
	int index = (int)((char*)ptr - _pool) / _unitSize;
	_use[index] = false;
}