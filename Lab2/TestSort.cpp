#include <iostream>
#include <cassert>

#include "Timer.h"
#include "ISorter.h"
#include "QuickSort.h"
#include "BubbleSort.h"
#include "ShellSort.h"
#include "ArraySequence.h"
#include "LinkedListSequence.h"
#include "Sequence.h"

int cmp_int(const int& a, const int& b) {
    return a - b;
}

int cmp_int_rev(const int& a, const int& b) {
    return b - a;
}

void TestQuickSort() {
    std::cout << "QuickSort" << std::endl;
    std::function<int(const int&, const int&)> comp;
    comp = cmp_int;
    int data[5] = { 0, 3,-5, 1,10 };
    for (int i = 0; i < 5; i++) {
        std::cout << data[i]  << " ";
    }
    std::cout << '\n';
    ISorter<int>* sorter = new QuickSorter<int>();
    Sequence<int>* seq = new ArraySequence<int>(data, 5);
    Sequence<int>* seq2 = sorter->Sort(seq, comp);
    assert(seq2->Get(0) == -5);
    assert(seq2->Get(1) == 0);
    assert(seq2->Get(2) == 1);
    assert(seq2->Get(3) == 3);
    assert(seq2->Get(4) == 10);
    for (int i = 0; i < seq2->GetLength(); i++) {
        std::cout << seq2->Get(i)  << " ";
    }
    std::cout << '\n';
    std::cout << "Success" << std::endl;
}

void TestBubbleSort() {
    std::cout << "BubbleSort" << std::endl;
    std::function<int(const int&, const int&)> comp;
    comp = cmp_int;
    int data[5] = { 5,4,1,2,3 };
    for (int i = 0; i < 5; i++) {
        std::cout << data[i]  << " ";
    }
    std::cout << '\n';
    ISorter<int>* sorter = new BubbleSorter<int>();
    Sequence<int>* seq = new ArraySequence<int>(data, 5);
    Sequence<int>* seq2 = sorter->Sort(seq, comp);
    assert(seq2->Get(0) == 1);
    assert(seq2->Get(1) == 2);
    assert(seq2->Get(2) == 3);
    assert(seq2->Get(3) == 4);
    assert(seq2->Get(4) == 5);
    for (int i = 0; i < seq2->GetLength(); i++) {
        std::cout << seq2->Get(i)  << " ";
    }
    std::cout << '\n';
    std::cout << "Success" << std::endl;
}

void TestShellSort() {
    std::cout << "ShellSort" << std::endl;
    std::function<int(const int&, const int&)> comp;
    comp = cmp_int;
    int data[5] = { 1,-1,2,-2,3 };
    for (int i = 0; i < 5; i++) {
        std::cout << data[i]  << " ";
    }
    std::cout << '\n';
    ISorter<int>* sorter = new ShellSorter<int>();
    Sequence<int>* seq = new ArraySequence<int>(data, 5);
    Sequence<int>* seq2 = sorter->Sort(seq, comp);
    assert(seq2->Get(0) == -2);
    assert(seq2->Get(1) == -1);
    assert(seq2->Get(2) == 1);
    assert(seq2->Get(3) == 2);
    assert(seq2->Get(4) == 3);
    for (int i = 0; i < seq2->GetLength(); i++) {
        std::cout << seq2->Get(i) << " ";
    }
    std::cout << '\n';
    std::cout << "Success" << std::endl;
}

int main() {
    TestQuickSort();
    TestBubbleSort();
    TestShellSort();
    return 0;
}