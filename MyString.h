#pragma once
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable 4996)
#include <fstream>
#include <cstring>
#include "Array.hpp"

class String {
public:
    String();
    String(const char*);
    String(const String&);
    String(int n);
    String(String&&) noexcept;
    String& operator=(String&& other)noexcept;
    String& operator=(const String&);
    int compareTo(const String& other) const;
    String concat(const String& other) const;
    Array<String> split(const String& other) const;
    String operator +(const String& other);
    void operator +=(const String& other);
    void operator +=(char ch);
    static int my_atoi(const String& myString);
    char& operator[](int index);
    const char& operator[](int index) const;
    friend std::ostream& operator <<(std::ostream&, const String&other);
    friend std::istream& operator >>(std::istream&, String&other);
    bool contains(const String& text) const;
    bool equals(const String& text) const;
    int IndexOf(const String& text) const;
    bool Ends(const String& text) const;
    bool isEmpty() const;
    int getLength() const;
    bool Starts(const String& text) const;
    String subStr(int, int endIndex = -1) const;
    String replace(const String& first , const String& sec) const;
    bool operator==(const String& text) const;
    bool operator!=(const String& text) const;
    bool operator<(const String& text) const;
    bool operator>(const String& text) const;
    bool operator<=(const String& text) const;
    bool operator>=(const String& text) const;
    String toUpperCase() const;
    String trim() const;
    const char* c_str() const;
    String IntToString(int number);
    ~String();
private:
    char* str;
    int length;
    int capacity;
    void copyFrom(const String&);
    void moveFrom(String&& other);
    void free();
    void resize();
};



