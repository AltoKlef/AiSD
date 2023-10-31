#pragma once
#ifndef DINARR_H
#define DINARR_H

template <class T>
class DinArr {
private:
    int capacity; // Размер массива
    int length;   // Текущее количество элементов
    T* arr;       // Динамический массив

public:
    DinArr();
    DinArr(int initialSize);
    DinArr(const DinArr<T>& other);
    DinArr<T>& operator=(const DinArr<T>& other);
    T& operator[](int index);
    void push_back(const T& value);
    void add(int index, const T& value);
    void remove(int index);
    int size() const;
    ~DinArr();
};
#include <iostream>
using namespace std;
class OutOfBoundsException : public runtime_error {
public:
    OutOfBoundsException(const string& message) : runtime_error(message) {
        cerr << message;
    }
};//это прикол

template <class T>
DinArr<T>::DinArr() {
    length = 0;
    capacity = 20;
    arr = new T[capacity];
}

template <class T>
DinArr<T>::DinArr(int initialSize) {
    length = initialSize;
    capacity = length + 20;
    arr = new T[capacity];
}

template <class T>
DinArr<T>::DinArr(const DinArr<T>& other) {
    length = other.length;
    capacity = other.capacity;
    arr = new T[length];

    for (int i = 0; i < length; i++) {
        arr[i] = other.arr[i];
    }
}

template <class T>
DinArr<T>& DinArr<T>::operator=(const DinArr<T>& other) {
    if (this == &other) {
        return *this;
    }

    delete[] arr;
    length = other.length;
    arr = new T[length];

    for (int i = 0; i < length; i++) {
        arr[i] = other.arr[i];
    }

    return *this;
}

template <class T>
T& DinArr<T>::operator[](int index) {
    if (index >= 0 && index < length) {
        return arr[index];
    }
    else {
        throw OutOfBoundsException("Error: accessing uninitialized memory");
    }
}

template <class T>
void DinArr<T>::push_back(const T& value) {
    if (length >= capacity) {
        capacity += 20;
        T* temp = new T[capacity];
        for (int i = 0; i < length; i++) {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }
    arr[length] = value;
    length++;
}

template <class T>
void DinArr<T>::add(int index, const T& value) {
    if (index >= 0 && index < length) {
        if (length >= capacity) {
            capacity += 20;
            T* temp = new T[capacity];
            for (int i = 0; i < length; i++) {
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;
        }

        for (int i = length; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        arr[index] = value;
        length++;
    }
    else {
        throw OutOfBoundsException("Error: accessing uninitialized memory");
    }
}

template <class T>
void DinArr<T>::remove(int index) {
    if (index >= 0 && index < length) {
        for (int i = index; i < length - 1; i++) {
            arr[i] = arr[i + 1];
        }
        length--;
    }
    else {
        throw OutOfBoundsException("Error: accessing uninitialized memory");
    }
}

template <class T>
int DinArr<T>::size() const {
    return length;
}

template <class T>
DinArr<T>::~DinArr() {
    delete[] arr;
}

#endif
