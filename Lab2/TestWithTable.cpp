#include <iostream>
#include <functional>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "BubbleSort.h"
#include "QuickSort.h"
#include "Timer.h"
#include "ShellSort.h"
#include "ArraySequence.h"

#define COUNT 10
using namespace std;

int cmp_int(const int& a, const int& b) {
	return a - b;
}

float TimeSort(int amount, ISorter<int>* sorter) {
	float time = 0;
	Timer t;
	for (int j = 0; j < COUNT; j++) {
		int* data = new int[amount];
		for (int i = 0; i < amount; i++) {
			data[i] = rand() % 50000;
		}
		Sequence<int>* seq = new ArraySequence<int>(data, amount);
		t.TimeStart();
		sorter->Sort(seq, cmp_int);
		time += t.GetTime();
		seq->~Sequence();
		delete[] data;
	}
	return (time / COUNT);
}

int main() {
	srand(time(nullptr));
	ofstream filename("Table3.csv");
	int data[16] = { 0, 2000, 4000, 6000, 8000, 10000, 12000, 14000, 16000, 18000, 20000, 22000, 24000, 26000, 28000, 30000};
	ISorter<int>* sort1 = new QuickSorter<int>;
	ISorter<int>* sort2 = new BubbleSorter<int>;
	ISorter<int>* sort3 = new ShellSorter<int>;
	float time1, time2, time3;
	filename << "BubbleSort;" << "\n";
	for (int i = 11; i < 15; i++) {
		//time1 = TimeSort(data[i], sort1);
		time2 = TimeSort(data[i], sort2);
		//time3 = TimeSort(data[i], sort3);
		//filename << time2 << ";" << time3 << ";\n";

		cout << data[i] << " " << time2 << "\n";
		//filename << time3 << ";\n";
	}
	filename.close();
	return 0;
}

