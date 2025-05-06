#pragma once

#include <iostream>
#include "DynamicArray.h"
#include <stdexcept>

using namespace std;

template <typename T> 
class UnqPtr {
	private:
		T* ptr;
	public:
		// конструкторы
		UnqPtr() {
			ptr = nullptr;
		}

		UnqPtr(T* other) {
			ptr = other;
		}

		UnqPtr(UnqPtr<T>&& other) {
			this->ptr = other.ptr;
			other.ptr = nullptr;
		}
		// деструктор 
		~UnqPtr() {
			cout << "Deleting ptr" << endl;
			delete ptr;
		}
		
		void Swap(UnqPtr<T>& other) {
			T* ptr2 = this->ptr;
			this->ptr = other.ptr;
			other.ptr = ptr2;
		}

		T* Release() {
			T* ptr2 = this->ptr;
			this->ptr = nullptr;
			return ptr2;
		}

		T* Get() {
			return ptr;
		}

		void Reset() {
			delete ptr;
            ptr = nullptr;
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
                std::cout << "Deleting shared pointer..." << std::endl;
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
                std::cout << "Deleting shared pointer..." << std::endl;
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
                std::cout << "Deleting shared pointer..." << std::endl;
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

    int GetCount() {
        return *counter;
    }

    bool Expired() {
        return GetCount() == 0;
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
    }

    MsPtr(const DynamicArray<T>& other) {
        this->ptr = new DynamicArray<T>(other);
        this->counter = new int(1);
    }

    ~MsPtr() {
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
                std::cout << "Deleting shared pointer..." << std::endl;
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

    int* GetCounter() {
        return counter;
    }

    MsPtr<T>& operator=(const MsPtr<T>& other) {
        if (counter) {
            (*counter)--;
            if (*counter <= 0) {
                std::cout << "Deleting shared pointer..." << std::endl;
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
                std::cout << "Deleting shared pointer..." << std::endl;
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

    ~MemorySpan() {
        if (ptr.GetCounter()) {
            (*(ptr.GetCounter()))--;
            if (*(ptr.GetCounter()) <= 0) {
                //std::cout << "Deleting shared pointer..." << std::endl;
                delete this->ptr.Get();
                delete this->ptr.GetCounter();
            }
        }
    }

    ShrdPtr<T> Copy(int index) {
        ShrdPtr<T> pointer = nullptr;
        pointer.ptr = new T((*(this->ptr.ptr))[index]);
        pointer.counter = new int(1);
        return pointer;
    }

    
};