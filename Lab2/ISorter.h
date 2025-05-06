#pragma once

#include "Pointer.h"
#include "Sequence.h"
#include <functional>

template <typename T>
class ISorter
{
public:
	virtual ~ISorter() { }

	virtual void Sort(Sequence<T>* sequence, std::function<int(const T&, const T&)> comp) = 0;

	virtual Sequence<T>* SortCopy(Sequence<T>* sequence, std::function<int(const T&, const T&)> comp) = 0;
};