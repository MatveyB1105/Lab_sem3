#pragma once

#include <stdexcept>

template <typename T> class DynamicArray {
    private:    
        T* data = nullptr;
        int lenght;
    public:
    // создание обьекта
        DynamicArray(const T* items, int count) { // Копировать элементы из переданного массива
            data = new T[count];
            lenght = count;
            for(int i = 0; i < count; i++) {
                data[i] = items[i];
            }
        }
        DynamicArray(int size) { // Создать массив заданной длины
            data = new T[size];
            lenght = size;
        }
        DynamicArray(const DynamicArray<T>& dynamicArray) { // Копирующий конструктор
            lenght = dynamicArray.lenght;
            data = new T[lenght];
            for(int i = 0; i < lenght; i++) {
                data[i] = dynamicArray.Get(i);
            }
        }
    // Декомпозиция
        T& Get(const int index) const {
            if(index < 0 || index >= lenght) {
                throw std::out_of_range("Out of Range");
            }
            return this->data[index];
        }
        int GetSize() {
            return lenght;
        }
    // Операции
        void Set(int index, T value) {
            if(index < 0 || index >= lenght) {
                throw std::out_of_range("Out of Range");
            }
            data[index] = value;
        }
        void Resize(int newSize, T value) {
            if(newSize <= 0) {
                throw std::out_of_range("Out of Range");
            }
            T* newData = new T[newSize];
            int tempSize = (newSize > lenght) ? lenght : newSize; 
            for (int i = 0; i < tempSize; i++) {newData[i] = data[i];}
            for(int i = tempSize; i < newSize; i++) {newData[i] = value;}
            delete[] data;
            data = newData;
            lenght = newSize;
        }
        void ResizeRight(int newSize, T value) {
            if(newSize <= 0) {
                throw std::out_of_range("Out of Range");
            }
            T* newData = new T[newSize];
            int startIndex = (newSize > lenght) ? (newSize - lenght) : 0;
            for(int i = 0; i < startIndex; i++) {newData[i] = value;}
            for (int i = startIndex; i < newSize; i++) {newData[i] = data[i - startIndex];}
            delete data;
            data = newData;
            lenght = newSize;
        }
    // операторы
        T& operator[](int index) const {
            if (index < 0 || index >= lenght) {
                throw std::out_of_range("Out of range");
            }
            return data[index];
        }
    // деструктор класса 
        ~DynamicArray() {
            if(data) {
                delete[] data;
            }
        }
};