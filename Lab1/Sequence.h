#pragma once

template <class T> class Sequence
{
    public:
        virtual ~Sequence() {};
        virtual Sequence<T>* Create() = 0;

        virtual T GetFirst() const = 0;
	    virtual T GetLast() const = 0;	
	    virtual T Get(int index) const = 0;

        virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) = 0;
        virtual int GetLength() const  = 0;		

        virtual void Append(T item) = 0; 
        virtual void Prepend(T item) = 0; 
        virtual void InsertAt(T item, int index) = 0; 

        virtual Sequence <T>* Concat(Sequence <T>* list) = 0;

        Sequence<T>* map(T (*mapFunc)(T arg)) {
            if(this == NULL) {
                throw std::out_of_range("Out of Range");
            }
            Sequence<T>* result = this->Create();
            for(int i = 0; i < this->GetLength(); i++) {
                result->Append(mapFunc(this->Get(i)));
            }
            return result;
        }

        T reduce(T (*reducer)(T arg1, T arg2), T value) {
            if(this == NULL) {
                throw std::out_of_range("Out of Range");
            }
            T buf = value;
            for(int i = 0; i < this->GetLength(); i++) {
                buf = reducer(this->Get(i), buf);
            }
            return buf;
        }

        Sequence<T>* where(bool (*condition)(T arg)) {
            if(this == NULL) {
                throw std::out_of_range("Out of Range");
            }
            Sequence<T>* result = this->Create();
            for(int i = 0; i < this->GetLength(); i++) {
                if(condition(this->Get(i))) {
                    result->Append(this->Get(i));
                }
            }
            return result;
        }
        
};