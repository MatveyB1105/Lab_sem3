#include <iostream>
#include "Pointer.h"
#include <cassert>
#include "ArraySequence.h"

void TestUnqPtr() {
	std::cout << "Test of UnqPtr" << std::endl;
	std::cout << "UnqPtr<Sequence<int>> ptr = nullptr" << std::endl;
	UnqPtr<Sequence<int>> ptr;
	assert(ptr.Get() == nullptr);
	int data[5] = { 1,2,3,4,5 };
	Sequence<int>* seq = new ArraySequence<int>(data,5);
	UnqPtr<Sequence<int>> ptr2(seq);
	assert((*ptr2).GetLength() == 5);
	ptr.Swap(ptr2);
	assert(ptr2.Get() == nullptr);
	assert(ptr->GetLength() == 5);
	std::cout << ptr->GetFirst() << std::endl;
	std::cout << "Success" << std::endl;
}

void TestShrdPtr() {
	std::cout << "Test of ShrdPtr" << std::endl;
	ShrdPtr<Sequence<int>> ptr;
	assert(ptr.Get() == nullptr);
	assert(ptr.UseCount() == 0);
	int data[3] = { 1,2,3 };
	ShrdPtr<Sequence<int>> ptr2(new ArraySequence<int>(data,3));
	assert(ptr2->GetLength() == 3);
	ShrdPtr<Sequence<int>> ptr3 = ptr;
	assert(ptr3.Unique());
	std::cout << ptr3.UseCount() << "\n";
	std::cout << "Success" << std::endl;
}

void TestMemorySpan() {
	std::cout << "Test of MemorySpan" << std::endl;
	int* data = new int[5];
	for (int i = 0; i < 5; i++) {
		data[i] = i;
	}
	MemorySpan<int> ptr1 = MemorySpan<int>(data, 5);
	assert(ptr1.Get(2) == 2);
	std::cout << "Success" << std::endl;
}

void TestMsPtr() {
	std::cout << "Test of MsPtr" << std::endl;
	int* data = new int[5];
	for (int i = 0; i < 5; i++) {
		data[i] = i;
	}
	MsPtr<int> data2(data, 5);
	std::cout << "Success" << std::endl;
}

int main() {
	TestMsPtr();
	return 0;
}
	