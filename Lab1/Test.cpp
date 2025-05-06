#include <iostream>
#include "Pointer.h"
#include "ArraySequence.h"
#include <cassert>
using namespace std;

void TestUnqPtr() {
    srand(time(nullptr));
    int* data = new int[5];
    for (int i = 0; i < 5; i++) {
        data[i] = rand() % 100;
    }
    int a = 5;
    UnqPtr<int> ptr = UnqPtr<int>();
    Sequence<int>* seq = new ArraySequence<int>(data, 5);
    UnqPtr<int> ptr2(new int(a));
    assert(*ptr2 == 5);
    assert(*(ptr2.Get()) == 5);
    UnqPtr<Sequence<int>> ptr3 = UnqPtr<Sequence<int>>(seq);
    assert(ptr3->Get(0) == seq->Get(0));
    assert(ptr3->Get(1) == seq->Get(1));
    assert(ptr3->Get(2) == seq->Get(2));
    assert(ptr3->Get(3) == seq->Get(3));
    assert(ptr3->Get(4) == seq->Get(4));
    *ptr2 = 7;
    assert(*ptr2 == 7);
    ptr2.Swap(ptr);
    assert(*ptr == 7);
    assert(ptr2.Get() == nullptr);
    ptr.Reset();
    assert(ptr.Get() == nullptr);
    delete[] data;
}

void TestShrdPtr() {
    srand(time(nullptr));
    int* data = new int[5];
    for (int i = 0; i < 5; i++) {
        data[i] = rand() % 100;
    }
    int a = 5;
    ShrdPtr<int> ptr = ShrdPtr<int>();
    Sequence<int>* seq = new ArraySequence<int>(data, 5);
    ShrdPtr<int> ptr2(new int(a));
    assert(ptr2.UseCount() == 1);
    assert(ptr2.Unique() == true);
    ShrdPtr<int> ptr4 = ShrdPtr<int>(ptr2);
    assert(ptr2.UseCount() == 2);
    assert(ptr2.Unique() == false);
    assert(*ptr2 == 5);
    assert(*(ptr2.Get()) == 5);
    ShrdPtr<Sequence<int>> ptr3 = ShrdPtr<Sequence<int>>(seq);
    assert(ptr3->Get(0) == seq->Get(0));
    assert(ptr3->Get(1) == seq->Get(1));
    assert(ptr3->Get(2) == seq->Get(2));
    assert(ptr3->Get(3) == seq->Get(3));
    assert(ptr3->Get(4) == seq->Get(4));
    *ptr2 = 7;
    assert(*ptr2 == 7);
    ptr2.Swap(ptr);
    assert(*ptr == 7);
    assert(ptr2.Get() == nullptr);
    ptr.Reset();
    assert(ptr.Get() == nullptr);
    delete[] data;
}


int main() {
    TestUnqPtr();
    std::cout << "Test of UnqPtr completed successfully" << std::endl;
    TestShrdPtr();
    std::cout << "Test of ShrdPtr completed successfully" << std::endl;
    return 0;
}