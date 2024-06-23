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
    String(String&&);
    String& operator =(String&&);
    String& operator =(const String&);
    char charAt(int) const;
    int compareTo(const String&) const;
    String concat(const String&) const;
    Array<String> split(const String&) const;
    String operator +(const String&);
    void operator +=(const String&);
    void operator +=(char ch);
    static int my_atoi(const String& myString);
    char& operator[](int index);
    const char& operator[](int index) const;
    friend std::ostream& operator <<(std::ostream&, const String&other);
    friend std::istream& operator >>(std::istream&, String&other);
    bool contains(const String&) const;
    bool equals(const String&) const;
    int IndexOf(const String&) const;
    bool Ends(const String&) const;
    bool isEmpty() const;
    int getLength() const;
    bool Starts(const String&) const;
    String subStr(int, int endIndex = -1) const;
    String replace(const String&, const String&) const;
    bool operator==(const String&) const;
    bool operator!=(const String&) const;
    bool operator<(const String&) const;
    bool operator>(const String&) const;
    bool operator<=(const String&) const;
    bool operator>=(const String&) const;
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
    void free();
    void resize();
};



