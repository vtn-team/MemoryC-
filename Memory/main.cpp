#include <iostream>
#include <vector>
#include <chrono>

#include "mempool.h"
#include "operator.h"

int main(int argc, char const* argv[])
{
    //�������v�[��
    MemoryPool* pool = MemoryPool::create(100000, 8);

    //�v��
    std::chrono::system_clock::time_point  start, end;

    //���ꂼ��̕��׌v��
    //new�̑��x��r
    start = std::chrono::system_clock::now(); // �v���J�n����
    for (int i = 0; i < 25000; ++i)
    {
        int* a = pool->New<int>();
        double* b = pool->New<double>();
    }
    end = std::chrono::system_clock::now();  // �v���I������
    double elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "placement new:" << elapsed << "microsec" << std::endl;

    start = std::chrono::system_clock::now(); // �v���J�n����
    for (int i = 0; i < 25000; ++i)
    {
        int* a = new int;
        double* b = new double;
    }
    end = std::chrono::system_clock::now();  // �v���I������
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "normal new:" << elapsed << "microsec" << std::endl;

    int* leaktest = NEW int;

    //��������̔z�u������
    /*
    int* a = pool->New<int>();
    double* b = pool->New<double>();
    *a = 1;
    *b = 0.1;
    std::cout.setf(std::ios::hex);
    for (int i = 0; i < 100; ++i)
    {
        printf("%1x \n", (*pool->GetData(i)));
    }
    pool->Free(b);
    pool->Free(a);
    */

    //�J�X�^���A���P�[�^
    /*
    MemoryPool* pool2 = MemoryPool::create(100000, 16);
    AllocatorMemory::setPool(pool2);
    std::vector<int, Allocator<int>> myVector;
    myVector.resize(3);
    myVector.push_back(1);
    myVector.push_back(2);
    myVector.push_back(3);
    myVector.push_back(4);
    */

    //���[�N�`�F�b�N
    //leakdump();

    return 0;
}