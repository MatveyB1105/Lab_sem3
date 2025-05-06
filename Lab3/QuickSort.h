#pragma once

#include "ISorter.h"
#include "Sequence.h"

template <typename T>
class QuickSorter : public ISorter<T>
{
public:
	void Sort(Sequence<T>* sequence, std::function<int(const T&, const T&)> comp) override
	{
		if (sequence->GetLength() == 0) {
			return;
		}
		QuickSort(sequence, comp, 0, sequence->GetLength() - 1);
	}
	Sequence<T>* SortCopy(Sequence<T>* sequence, std::function<int(const T&, const T&)> comp) override
	{
		if (sequence->GetLength() == 0) {
			return sequence->Create();
		}
		Sequence<T>* copy = sequence->Copy();
		QuickSort(copy, comp, 0, copy->GetLength() - 1);
		return copy;
	}
private:
	void QuickSort(Sequence<T>* sequence, std::function<int(const T&, const T&)> comp, int start, int end)
	{
		if (start >= end) {
			return;
		}
		int pivot = partition(sequence, comp,  start, end);
		QuickSort(sequence, comp, start, pivot - 1);
		QuickSort(sequence, comp, pivot + 1, end);
	}
    int partition(Sequence<T>* sequence, std::function<int(const T&, const T&)> comp, int start, int end)
    {
		int pivot = sequence->Get(end);
		int pIndex = start;
		for (int i = start; i < end; i++) {
			if (comp(sequence->Get(i), pivot) <= 0) {
				std::swap(sequence->Get(i), sequence->Get(pIndex));
				pIndex++;
			}
		}
		std::swap(sequence->Get(pIndex), sequence->Get(end));
		return pIndex;
    }
};