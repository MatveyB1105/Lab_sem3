#pragma once

#include "LinkedList.h"
#include "Sequence.h"

template <typename T> class LinkedListSequence: public Sequence<T>
{ 
    private:
        LinkedList<T>* inlist;
    public:
        LinkedListSequence(T* items, int count) { //Копировать элементы из переданного массива
            inlist = new LinkedList<T>(items, count);
        }
        LinkedListSequence() { //Создать пустой список
            inlist = new LinkedList<T>();
        }
        LinkedListSequence(const Sequence<T>& list) { //Копирующий конструктор
            inlist = new LinkedList<T>();
            for(int i = 0; i < list.GetLength(); i++) {
                this->Append(list.Get(i));
            }
        }

        Sequence<T>* Create() override {
            return (Sequence<T>*) new LinkedListSequence<T>();
        }
        //Декомпозиция
        T GetFirst() const override{
            return inlist->GetFirst();
        }
        T GetLast() const override{
            return inlist->GetLast();
        }
        T Get(int index) const override{
            return inlist->Get(index);
        }
        Sequence<T>* GetSubsequence(int startIndex, int endIndex) override{
            if(startIndex < 0 || startIndex >= this->GetLength() || endIndex < 0 || endIndex >= this->GetLength()) { 
                throw std::out_of_range("Out of Range");
            }
            Sequence<T>* result = new LinkedListSequence<T>();
            for(int i = startIndex; i < endIndex; i++) {
                result->Append(this->Get(i));
            }
            return result;
        }
        int GetLength() const override{
            return inlist->GetLength();
        }
        // Операции
        void Append(T item) override{
            inlist->Append(item);
        }
        void Prepend(T item) override{
            inlist->Prepend(item);
        }
        void InsertAt(T item, int index) override{
            inlist->InsertAt(item, index);
        }
        Sequence<T>* Concat(Sequence <T>* list) override{
            Sequence<T>* result = new LinkedListSequence<T>();
            for(int i = 0; i < this->GetLength(); i++) {
                result->Append(this->Get(i));
            }
            for(int i = 0; i < list->GetLength(); i++) {
                result->Append(list->Get(i));
            }
            return result;
        }
        ~LinkedListSequence() {
            delete inlist;
	    }
};