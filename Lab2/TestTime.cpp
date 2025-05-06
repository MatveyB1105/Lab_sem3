#include <iostream>
#include <functional>
#include "BubbleSort.h"
#include "QuickSort.h"
#include "Timer.h"
#include "ShellSort.h"
#include "ArraySequence.h"

// ����� �� ������ ArraySequence
using namespace std;

int cmp_int(const int& a, const int& b) {
	return a - b;
}

int main() {
    srand(time(nullptr));
    int len, count, sort;
    ISorter<int>* sorter;
    cout << "Enter lenght: ";
    cin >> len;
    cout << "\n";

    cout << "Enter count of massives: ";
    cin >> count;
    cout << "\n";

    cout << "Enter sort (1 - bubble, 2 - shell, 3 - quick): ";
    cin >> sort;
    cout << "\n";
    switch (sort) {
    case 1:
        sorter = (new BubbleSorter<int>);
        break;
    case 2:
        sorter = (new ShellSorter<int>);
        break;
    case 3:
        sorter = (new QuickSorter<int>);
        break;
    }

    Timer time;
    for (int j = 0; j < count; j++) {
        int* data = new int[len];
        for (int i = 0; i < len; i++) {
            data[i] = rand() % 1000;
        }
        Sequence<int>* seq = new ArraySequence<int>(data, len);
        Sequence<int>* result = sorter->Sort(seq, cmp_int);
        delete[] data;
    }
    cout << "time of sort: " << time.GetTime()/count << endl;
    return 0;
}