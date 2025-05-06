#pragma once 
#include <iostream>
#include <stdexcept>
#include "DynamicArray.h"
template <typename T>
class UnqPtr {
private:
    T* ptr;

public:
    UnqPtr() {
        ptr = nullptr;
    }


    UnqPtr(UnqPtr<T>& other) {
        this->ptr = other.ptr;
        other.ptr = nullptr;
    }

    UnqPtr(UnqPtr<T>&& other) {
        this->ptr = other.ptr;
        other.ptr = nullptr;
    }

    UnqPtr(T* other) {
        this->ptr = other;

    }

    ~UnqPtr() {
        //std::cout << "Deleting unique pointer..." << std::endl;
        delete ptr;
    }

    T* Release() {
        T* tmp = this->ptr;
        this->ptr = nullptr;
        return tmp;
    }

    void Reset(T* other) {
        delete ptr;
        ptr = other;
    }

    void Swap(UnqPtr<T>& other) {
        T* tmp = this->ptr;
        this->ptr = other.ptr;
        other.ptr = tmp;
    }

    T* Get() {
        return this->ptr;
    }

    UnqPtr<T>& operator=(UnqPtr<T>& other) {
        this->ptr = other.ptr;
        other.ptr = nullptr;
        return *this;
    }

    UnqPtr<T>& operator=(UnqPtr<T>&& other) {
        this->ptr = other.ptr;
        other.ptr = nullptr;
        return *this;
    }

    UnqPtr<T>& operator=(T* other) {
        this->ptr = other;
        return *this;
    }

    operator bool() {
        return this->ptr;
    }

    T& operator*() {
        return *(this->ptr);
    }

    T* operator->() {
        return this->ptr;
    }

    T& operator[](int index) {
        if (index < 0) {
            throw std::out_of_range("Out of range");
        }
        return this->ptr[index];
    }
};

template <typename T>
class ShrdPtr {
private:
    T* ptr;
    int* counter;
public:
    ShrdPtr() {
        this->ptr = nullptr;
        this->counter = new int(0);
    }

    ShrdPtr(std::nullptr_t) {
        this->ptr = nullptr;
        this->counter = new int(0);
    }

    ShrdPtr(const ShrdPtr<T>& other) {
        this->ptr = other.ptr;
        this->counter = other.counter;
        (*this->counter)++;
    }

    ShrdPtr(T* other) {
        this->ptr = other;
        this->counter = new int(1);
    }

    ~ShrdPtr() {
        if (counter) {
            (*counter)--;
            if (*counter <= 0) {
                //std::cout << "Deleting shared pointer..." << std::endl;
                delete ptr;
                delete counter;
            }
        }
    }

    int UseCount() {
        return *this->counter;
    }

    bool Unique() {
        return *this->counter == 1;
    }

    void Reset() {
        if (counter) {
            (*counter)--;
            if (*counter <= 0) {
                //std::cout << "Deleting shared pointer..." << std::endl;
                delete ptr;
                delete counter;
            }
        }
        this->ptr = nullptr;
        this->counter = nullptr;
    }

    void Swap(ShrdPtr<T>& other) {
        T* tmp = this->ptr;
        int* tmp_counter = this->counter;
        this->ptr = other.ptr;
        other.ptr = tmp;
        this->counter = other.counter;
        other.counter = tmp_counter;
    }

    T* Get() {
        return this->ptr;
    }

    ShrdPtr<T>& operator=(const ShrdPtr<T>& other) {
        if (counter) {
            (*counter)--;
            if (*counter <= 0) {
                //std::cout << "Deleting shared pointer..." << std::endl;
                delete ptr;
                delete counter;
            }
        }
        this->ptr = other.ptr;
        this->counter = other.counter;
        (*this->counter)++;
        return *this;
    }

    ShrdPtr<T>& operator=(T* other) {
        if (counter) {
            (*counter)--;
            if (*counter <= 0) {
                //std::cout << "Deleting shared pointer..." << std::endl;
                delete ptr;
                delete counter;
            }
        }
        this->ptr = other;
        this->counter = new int(1);
        return *this;
    }

    operator bool() {
        return this->ptr;
    }

    T& operator*() {
        return *(this->ptr);
    }

    T* operator->() {
        return this->ptr;
    }

    T& operator[](int index) {
        if (index < 0) {
            throw std::out_of_range("Out of range");
        }
        return this->ptr[index];
    }

};

template <typename T>
class WeakPtr {
private:
    T* ptr;
    int* counter;
public:
    WeakPtr() {
        ptr = nullptr;
        counter = nullptr;
    }

    WeakPtr(const ShrdPtr<T>& other) {
        this->ptr = other.ptr;
        counter = other.counter;
        (*counter)++;

    }

    ~WeakPtr() = default;

    void Reset() {
        delete ptr;
    }

    void Swap(WeakPtr<T>& other) {
        T* tmp = this->ptr;
        this->ptr = other.ptr;
        other.ptr = tmp;
    }

    int UseCount() {
        return *counter;
    }

    bool Expired() {
        return UseCount() == 0;
    }

    ShrdPtr<T> Lock() {
        if (Expired()) {
            return ShrdPtr<T>(nullptr);
        }
        ShrdPtr<T> pointer = nullptr;
        pointer.ptr = this->ptr;
        pointer.counter = this->counter;
        (*counter)++;
        return pointer;

    }

    WeakPtr<T>& operator=(const ShrdPtr<T>& other) {
        this->ptr = other.ptr;
        this->counter = other.counter;
        return *this;
    }

    WeakPtr<T>& operator=(const WeakPtr<T>& other) {
        this->ptr = other.ptr;
        this->counter = other.counter;
        return *this;
    }
};

template <typename T>
class MsPtr {
private:
    DynamicArray<T>* ptr;
    int* counter;
public:
    MsPtr() {
        this->ptr = new DynamicArray<T>(0);
        this->counter = new int(0);
    }

    MsPtr(std::nullptr_t) {
        this->ptr = nullptr;
        this->counter = new int(0);
    }

    MsPtr(const MsPtr<T>& other) {
        this->ptr = other.ptr;
        this->counter = other.counter;
        (*this->counter)++;
    }

    MsPtr(T* other, int count) {
        this->ptr = new DynamicArray<T>(other, count);
        this->counter = new int(1);
        delete[] other;
    }

    MsPtr(const DynamicArray<T>& other) {
        this->ptr = new DynamicArray<T>(other);
        this->counter = new int(1);
    }

    ~MsPtr() {
        if (counter) {
            (*counter)--;
            if (*counter <= 0) {
                //std::cout << "Deleting master pointer..." << std::endl;
                delete ptr;
                delete counter;
            }
        }
    }

    int UseCount() {
        return *this->counter;
    }

    bool Unique() {
        return *this->counter == 1;
    }

    void Reset() {
        if (counter) {
            (*counter)--;
            if (*counter <= 0) {
                //std::cout << "Deleting master pointer..." << std::endl;
                delete ptr;
                delete counter;
            }
        }
        this->ptr = nullptr;
        this->counter = nullptr;
    }

    void Swap(MsPtr<T>& other) {
        T* tmp = this->ptr;
        int* tmp_counter = this->counter;
        this->ptr = other.ptr;
        other.ptr = tmp;
        this->counter = other.counter;
        other.counter = tmp_counter;
    }

    DynamicArray<T>* Get() {
        return this->ptr;
    }

    MsPtr<T>& operator=(const MsPtr<T>& other) {
        if (counter) {
            (*counter)--;
            if (*counter <= 0) {
                //std::cout << "Deleting master pointer..." << std::endl;
                delete ptr;
                delete counter;
            }
        }
        this->ptr = other.ptr;
        this->counter = other.counter;
        (*this->counter)++;
        return *this;
    }

    MsPtr<T>& operator=(T* other) {
        if (counter) {
            (*counter)--;
            if (*counter <= 0) {
                //std::cout << "Deleting master pointer..." << std::endl;
                delete ptr;
                delete counter;
            }
        }
        this->ptr = other;
        this->counter = new int(1);
        return *this;
    }

    operator bool() {
        return this->ptr;
    }

    T& operator*() {
        return *(this->ptr);
    }

    T* operator->() {
        return this->ptr;
    }

    T& operator[](int index) {
        if (index < 0) {
            throw std::out_of_range("Out of range");
        }
        return (*(this->ptr))[index];
    }
};
template<typename T>
class MemorySpan {
private:
    MsPtr<T> ptr;
public:
    MemorySpan() {
        this->ptr = MsPtr<T>();
    }

    MemorySpan(T* other, int count) {
        this->ptr = MsPtr<T>(other, count);
    }

    MemorySpan(const DynamicArray<T>& other) {
        this->ptr = MsPtr<T>(other);
    }

    MemorySpan(const MemorySpan<T>& other) {
        this->ptr = MsPtr<T>(other.ptr);
    }

    ShrdPtr<T> Copy(int index) {
        ShrdPtr<T> pointer = nullptr;
        pointer.ptr = new T((*(this->ptr.ptr))[index]);
        pointer.counter = new int(1);
        return pointer;
    }

    ~MemorySpan() = default;

    T& operator[](int index) {
        if (index < 0) {
            throw std::out_of_range("Out of range");
        }
        return (this->ptr)[index];
    }

    T& Get(int index) {
        return this->ptr[index];
    }

    MsPtr<T> Get() {
        return this->ptr;
    }
};