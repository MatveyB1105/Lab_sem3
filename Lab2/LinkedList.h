#pragma once

#include <stdexcept>

template <typename T> class Item {
    public:
        T data;	
        Item<T>* next;	
        Item<T>* previous;
};

template <typename T> class LinkedList {
    private:
        Item<T>* head;	// начало списка
        Item<T>* tail;  // конец списка
        int lenght;	// Длинна списка
    public:
    // создание обьекта
        LinkedList(T* items, int count) {
            head = NULL;
            tail = NULL;
            lenght = 0;
            for (int i = 0; i < count; i++) {
			    this->Append(items[i]);
		    }
        }
        LinkedList() {
            head = NULL;
            tail = NULL;
            lenght = 0;
        }
        LinkedList(const LinkedList<T>& list) {
            head = NULL;
            tail = NULL;
            lenght = 0;
		    for(int i = 0; i < list.GetLength(); i++) {
			    this->Append(list.Get(i));
		    }
	    } 
    // Декомпозиция   
        T& GetFirst() const {
            if(head == NULL) {
                throw std::out_of_range("Out of Range");
            }
		    return head->data; 
	    }
        T& GetLast() const {
            if(head == NULL) {
                throw std::out_of_range("Out of Range");
            }
            return tail->data;
        }
        T& Get(int index) const {
            if(index < 0 || index >= lenght) {
                throw std::out_of_range("Out of Range");
            }
            Item<T>* point = head;
            for (int i = 0; i < index; i++)
            {
                point = point->next;
            }
            return point->data;
        }
        LinkedList<T>* GetSubList(int startIndex, int endIndex) {
            if(startIndex < 0 || startIndex >= lenght || endIndex < 0 || endIndex >= lenght) { 
                throw std::out_of_range("Out of Range");
            }
            LinkedList<T>* point = new LinkedList<T>();
            for(int i = startIndex; i < endIndex; i++) {
                point->Append(Get(i));
            }
            return point;
        }
        int GetLength() const {
            return lenght;
        }
    // Операции
        void Append(T item) {
            Item<T>* buf = new Item<T>;
            buf->next = NULL;
            buf->data = item;
            if (head == NULL) {
                head = buf;
                tail = head;
            }
            else {
                buf->previous = tail;
                tail->next = buf;
                tail = buf; 
            }
            lenght++;	
        }
        void Prepend(T item) {
            Item<T>* buf = new Item<T>;
            buf->next = NULL;
            buf->data = item;
            if (head == NULL) {
                head = buf;
                head->previous = NULL;
                tail = head;
            }
            else {
                head->previous = buf;
                buf->next = head;
                head = buf; 
            }
            lenght++;	
	    }
        void InsertAt(T item, int index) {
            if(index < 0 || index > lenght) {
                throw std::out_of_range("Out of Range");
            }
            if(index == 0) {
                Prepend(item);
                return;
            }
            if(index == lenght - 1) {
                Append(item);
                return;
            } else {
                Item<T>* ptr = (*this)[index - 1];
                Item<T>* buf = new Item<T>;
                buf->data = item;
                buf->previous = ptr;
                buf->next = ptr->next;
                ptr->next->previous = buf;
                ptr->next = buf;
                lenght++;
            }
        }
        LinkedList<T>* Concat(LinkedList<T> *list) {
            for(int i = 0; i < list->lenght; i++) {
                Append(list->Get(i));
            }
            return this;
        }
    // операторы
        Item<T>* operator[](int index) {
		    if(index < 0 || index >= lenght) {
                throw std::out_of_range("Out of Range");
            }
            Item<T>* buf = head;
            for (int i = 0; i < index; i++)
            {
                buf = buf->next;
            }
            return buf;
        }
    // деструктор класса
        ~LinkedList() {
            if(!head) return;
            Item<T>* ptr = head, *prev;
            while(ptr) {
                prev = ptr;
                ptr = ptr->next;
                delete prev;
            }
            this->head = nullptr;
        }
};