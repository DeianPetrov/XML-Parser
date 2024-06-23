#pragma once
#include <iostream>
#include "MyString.h"

template<typename T, typename U>
struct MyPair {
    T key;
    U value;
    const T GetMyPairKey() const {
        return key;
    }
    const U GetMyPairValue() const {
        return value;
    }
    void SetMyPairKey(const T& k) {
        key = k;
    }
    void SetMyPairValue(const U& val) {
        value = val;
    }
};

template <typename T, typename U>
class MyMap {
    MyPair<T, U>* data;
    int size;
    int capacity;
    void resize();
    void free();
    void copyFrom(const MyMap< T, U >& other);
public:
    MyMap();
    MyMap(const MyMap< T, U>& other);
    MyMap<T, U >& operator=(const MyMap< T, U >& other);
    void add(const T& key, const U& value);
    bool remove(const T& key);
    const U& find(const T& key) const;
    const MyPair< T, U>* getMyPairs() const;
    bool hasKey(const T& key) const;
    bool setValue(const T& key, const U& value);
    void print() const;
    int getSize() const;
    void clear();
    ~MyMap();
};
template <typename T, typename U>
void MyMap<T, U>::clear() {
    free();
    capacity = 4;
    data = new MyPair< T, U>[capacity];
    size = 0;
}
template <typename T, typename U>
int MyMap<T, U>::getSize() const {
    return size;
}
template <typename T, typename U>
bool MyMap<T, U>::hasKey(const T& key) const {
    for (int i = 0; i < size; i++) {
        if (key == data[i].key)
            return true;
    }
    return false;
}
template <typename T, typename U>
bool MyMap<T, U>::setValue(const T& key, const U& value) {
    for (int i = 0; i < size; i++) {
        if (key == data[i].key) {
            data[i].value = value;
            return true;
        }
    }
    add(key, value);
    return true;
}
template <typename T, typename U>
const MyPair<T, U>* MyMap<T, U>::getMyPairs() const {
    return data;
}
template <typename T, typename U>
MyMap<T, U>::MyMap() {
    capacity = 4;
    size = 0;
    data = new MyPair<T, U>[capacity];
}
template <typename T, typename U>
MyMap<T, U>::MyMap(const MyMap<T, U>& other) {
    copyFrom(other);
}
template <typename T, typename U>
MyMap<T, U>::~MyMap() {
    free();
}
template <typename T, typename U>
MyMap<T, U>& MyMap<T, U>::operator=(const MyMap<T, U>& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}
template <typename T, typename U>
bool MyMap<T, U>::remove(const T& key) {
    int removeIndex = -1;
    for (int i = 0; i < size; i++)
        if (key == data[i].key) {
            removeIndex = i;
            break;
        }
    if (removeIndex == -1) return false;
    for (int i = removeIndex; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
    return true;
}
template <typename T, typename U>
void MyMap<T, U>::resize() {
    capacity *= 2;
    MyPair<T, U>* ptr = new MyPair<T, U>[capacity];
    for (int i = 0; i < size; i++)
        ptr[i] = data[i];
    free();
    data = ptr;
}
template<typename T, typename U>
void MyMap<T, U>::free()
{
    delete[] data;
   
}
template <typename T, typename U>
void MyMap<T, U>::copyFrom(const MyMap<T, U>& other) {
    size = other.size;
    capacity = other.capacity;
    data = new MyPair<T, U>[capacity];
    for (int i = 0; i < size; i++) {
        data[i] = other.data[i];
    }
}

template <typename T, typename U>
void MyMap<T, U>::add(const T& key, const U& value) {
    if (hasKey(key))
        throw String("Key is already added in collection!");
    if (size == capacity)
        resize();
    int insertIndex = size;
    for (int i = 0; i < size; i++) {
        if (key < data[i].key) {
            insertIndex = i;
            break;
        }
    }
    for (int i = size; i > insertIndex; i--) {
        data[i] = data[i - 1];
    }
    data[insertIndex] = { key, value };
    size++;
}
template <typename T, typename U>
const U& MyMap<T, U>::find(const T& key) const {
    for (int i = 0; i < size; i++)
        if (data[i].key == key)
            return data[i].value;
    throw String("No such key in MyMap!");
}
template <typename T, typename U>
void MyMap<T, U>::print() const {
    for (int i = 0; i < size; i++) {
        std::cout << data[i].key << " " << data[i].value
            << std::endl;
    }
}
