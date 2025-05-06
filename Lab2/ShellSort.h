#pragma once

#include "ISorter.h"
#include "Sequence.h"
#include <functional>

template <typename T>
class ShellSorter : public ISorter<T>
{
public:
	void Sort(Sequence<T>* sequence, std::function<int(const T&, const T&)> comparator) {
		for (int d = sequence->GetLength() / 2; d > 0; d /= 2)
		{
			for (int i = d; i < sequence->GetLength(); i++)
			{
				for (int j = i - d; j >= 0 && comparator(sequence->Get(j), sequence->Get(j + d)) > 0; j -= d)
				{
					std::swap(sequence->Get(j), sequence->Get(j + d));
				}
			}
		}
	}
	Sequence<T>* SortCopy(Sequence<T>* sequence, std::function<int(const T&, const T&)> comparator) override
	{
		Sequence<T>* copy = sequence->Copy();

		for (int d = copy->GetLength() / 2; d > 0; d /= 2)
		{
			for (int i = d; i < copy->GetLength(); i++)
			{
				for (int j = i - d; j >= 0 && comparator(copy->Get(j), copy->Get(j + d)) > 0; j -= d)
				{
					std::swap(copy->Get(j), copy->Get(j + d));
				}
			}
		}

		return copy;
	}
};