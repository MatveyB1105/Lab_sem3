#pragma once

#include "DynamicArray.h"
#include "Sequence.h"

template <typename T> class ArraySequence : public Sequence<T>
{
    private: 
        DynamicArray<T>* items;
    public:
        ArraySequence(T* array, int count) {  //Копировать элементы из переданного массива
            this->items = new DynamicArray<T>(array, count); 
        }
        ArraySequence(const DynamicArray<T>& array) {  //Копировать элементы из переданного массива
            this->items = new DynamicArray<T>(array);
        }
        ArraySequence() { //Создать пустой список
            this->items = new DynamicArray<T>(0);
        }
        ArraySequence(const Sequence<T>& list) { //Копирующий конструктор
            this->items = new DynamicArray<T>(list);
        }
        Sequence<T>* Create() override {
            return (Sequence<T>*) new ArraySequence<T>();
        }
        Sequence<T>* Copy() override {
            return (Sequence<T>*) new ArraySequence<T>(*this);
        }
        //Декомпозиция
        T& GetFirst() const override{
		    return this->items->Get(0);
        }
        T& GetLast() const override{
            return this->Get(items->GetSize()-1);
        }
        T& Get(int index) const override{
            return items->Get(index);
        }
        Sequence<T>* GetSubsequence(int startIndex, int endIndex) override{
            if(startIndex < 0 || startIndex >= this->GetLength() || endIndex < 0 || endIndex >= this->GetLength()) { 
                throw std::out_of_range("Out of Range");
            }
            Sequence<T>* result = new ArraySequence<T>();
            for(int i = startIndex; i < endIndex; i++) {
                result->Append(Get(i));
            }
            return result;
        }
        int GetLength() const override{
            return items->GetSize();
        }
        // Операции
        void Append(T item) override{
            items->Resize(items->GetSize() + 1, 0);
            items->Set(items->GetSize()-1, item);
        }
        void Prepend(T item) override{
            items->ResizeRight(items->GetSize() + 1, 0);
            items->Set(0, item);
        }
        void InsertAt(T item, int index) override{
            this->items->Resize(this->items->GetSize() + 1, 0);
            this->items->Set(index, item);
	    }
        Sequence <T>* Concat(Sequence <T>* list) override{
            Sequence <T>* result = new ArraySequence<T>();
            for(int i = 0; i < this->GetLength(); i++) {
                result->Append(this->Get(i));
            }
            for(int i = 0; i < list->GetLength(); i++) {
                result->Append(list->Get(i));
            }
            return result;
        }

        T& operator[](int index) const {
            if (index < 0 || index >= this->GetLength()) {
                throw std::out_of_range("Out of range");
            }
            return this->Get(index);
        }

        // деструктор класса
        ~ArraySequence() {
            delete items;
        }
};