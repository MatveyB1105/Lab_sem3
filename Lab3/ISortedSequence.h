#pragma once

#include <iostream>
#include "Sequence.h"
#include "ISorter.h"
#include <stdexcept>
#include <functional>
template <typename T>
class SortedSequence {
private: 
	ISorter<T>* sorter;
	Sequence<T>* sequence;
	std::function<int(const T&, const T&)> comparator;
public:
	SortedSequence(Sequence<T>* seq, ISorter<T>* sort, std::function<int(const T&, const T&)> comp) {
		this->sequence = sort->SortCopy(seq,comp);
		this->sorter = sort;
		this->comparator = comp;
	}
	SortedSequence(const SortedSequence<T>& other) {
		this->sorter = other.sorter->SortCopy();
		this->sequence = other.sequence->Copy();
		this->comparator = other.comparator;
	}
	~SortedSequence() {
		delete sequence;
		delete sorter;
	}
	int GetLength() {
		return sequence->GetLength();
	}
	bool IsEmpty() const {
		if (sequence->GetLength() == 0) { return true; }
		else { return false; }
	}
	T& Get(int index) const{
		return sequence->Get(index);
	}
	T& GetFirst() const{
		return sequence->GetFirst();
	}
	T& GetLast() const{
		return sequence->GetLast();
	}
	T& operator[](int index) {
		return Get(index);
	}
	int IndexOf(const T& element) {
		for (int i = 0; i < GetLength(); i++) {
			if (Get(i) == element) {
				return i;
			}
		}
		return -1;
	}
	SortedSequence<T>* GetSubsequence(int start, int end) {
		return new SortedSequence(sequence->GetSubsequence(start, end), this->sorter, this->comparator);
	}
	void Add(const T& element) {
		if (IsEmpty()) {
			sequence->Append(element);
			return;
		}
		if (comparator(element, GetFirst()) <= 0) {
			sequence->Prepend(element);
			return;
		}
		if (comparator(element, GetLast()) >= 0) {
			sequence->Append(element);
			return;
		}
		for (int i = 0; i < GetLength(); i++) {
			if (comparator(element, Get(i)) <= 0) {
				this->sequence->InsertAt(element, i - 1);
					return;
			}
		}
	}
};
