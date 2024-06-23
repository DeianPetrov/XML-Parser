#pragma once
#include <iostream>
template <typename T>
class Array {
protected:
    T** data;
    int size;
    size_t capacity;
    void resize();
    void copyFrom(const Array<T>& other);
    void moveFrom(Array&& other);
    void free();
public:
    Array();
    Array(size_t cap);

    Array(const Array<T>& other);
    Array(Array<T>&& other) noexcept;
    Array<T>& operator=(Array<T>&& other)noexcept;
    Array<T>& operator=(const Array<T>& other);
    bool Add(const T& element);
    bool Add(T&& element) noexcept;
    bool remove(const T&);
    bool removeByIndex(int);
    bool find(const T&) const;
    int IndexOf(const T&) const;
    T& operator[](int);
    const T& operator[](int) const;
    Array<T>& operator+=(const Array<T>&);
    Array<T>& operator+=(const T& el);
    int getSize() const;
    bool isEmpty() const;
    void clear();
    ~Array();
};
template <typename T>
Array<T>::Array(Array<T>&& other)noexcept {
    moveFrom(std::move(other));
}
template <typename T>
Array<T>& Array<T>::operator=(Array<T>&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}
template <typename T>
void Array<T>::resize() {
    capacity *= 2;
    T** ptr = new T * [capacity];
    for (int i = 0; i < size; i++) {
        ptr[i] = new T(*data[i]);
    }
    free();
    data = ptr;
}
template <typename T>
void Array<T>::copyFrom(const Array<T>& other) {
    capacity = other.capacity;
    size = other.size;
    data = new T*[capacity];
    for (int i = 0; i < size; i++) {
        data[i] = new T(*(other.data[i]));
    }
}
template<typename T>
inline void Array<T>::moveFrom(Array&& other)
{
    data = other.data;
    other.data = nullptr;
    capacity = other.capacity;
    size = other.size;
}
template <typename T>
void Array<T>::free() {
    for (int i = 0; i < size; i++)
        delete data[i];
    delete[] data;
}
template <typename T>
Array<T>::Array() {
    capacity = 4;
    data = new T * [capacity];
    size = 0;
}
template<typename T>
inline Array<T>::Array(size_t cap)
{
    capacity = cap;
    data = new T * [capacity];
    size = 0;
}
template <typename T>
Array<T>::Array(const Array<T>& other) {
    copyFrom(other);
}
template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}
template <typename T>
bool Array<T>::Add(const T& el) {
    if (size == capacity)
        resize();
    data[size++] = new T(el);
    return true;
}
template <typename T>
bool Array<T>::Add(T&& el) noexcept{
    if (size == capacity) {
        resize();
    }
    data[size++] = new T(el);
    return true;
}
template <typename T>
bool Array<T>::remove(const T& el) {
    int elIndex = IndexOf(el);
    if (elIndex == -1) return false;
    for (int i = elIndex; i < size - 1; i++)
        data[i] = data[i + 1];
    size--;
    return true;
}
template <typename T>
bool Array<T>::removeByIndex(int index) {
    if (index < 0 || index >= size)
        return false;
    for (int i = index; i < size - 1; i++)
        data[i] = data[i + 1];
    size--;
    return true;
}
template <typename T>
int Array<T>::IndexOf(const T& el) const {
    for (int i = 0; i < size; i++)
        if (el == *data[i])
            return i;
    return -1;
}
template <typename T>
bool Array<T>::find(const T& element) const {
    return IndexOf(element) != -1;
}
template <typename T>
T& Array<T>::operator[](int index) {
    if (index < 0 || index >capacity) 
        throw 0;
    return *data[index];
}
template <typename T>
const T& Array<T>::operator[](int index) const {
    if (index < 0 || index > capacity)
        throw 0;
    return *data[index];
}
template <typename T>
Array<T>& Array<T>::operator+=(const Array<T>& other) {
    for (int i = 0; i < other.size; i++) {
        Add(*other.data[i]);
    }
    return *this;
}
template <typename T>
Array<T>& Array<T>::operator+=(const T& element) {
    Add(element);
    return *this;
}
template <typename T>
int Array<T>::getSize() const {
    return size;
}
template <typename T>
bool Array<T>::isEmpty() const {
    return size == 0;
}
template <typename T>
void Array<T>::clear() {
    free();
    capacity = 4;
    data = new T * [capacity];
    size = 0;
}
template <typename T>
Array<T>::~Array() {
    free();
}

