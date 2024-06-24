#include "MyString.h"

using namespace std;

bool isPrefix(const char* where, const char* what) {
    int whereLength = strlen(where);
    int whatLength = strlen(what);
    for (int i = 0; i < whatLength; i++) {
        if (where[i] != what[i]) return false;
    }
    return true;
}

void String::copyFrom(const String& string) {
    this->str = new char[string.length + 1];
    strcpy(this->str, string.str);
    this->length = string.length;
}
void String::moveFrom(String&& other)
{
    str = other.str;
    other.str = nullptr;
    length = other.length;
    capacity = other.capacity;
}
void String::free() {
    delete[] str;
}

void String::resize() {
    capacity *= 2;
    char* ptr = new char[capacity];
    for (int i = 0; i < length; i++) {
        ptr[i] = str[i];
    }
    ptr[length] = '\0';
    free();
    str = ptr;
}

String::String() {
    capacity = 2;
    str = new char[capacity];
    str[0] = '\0';
    length = 0;
}
String::String(const char* str) {
    capacity = 2;
    int length = strlen(str);
    this->str = new char[length + 1 + capacity];
    strcpy(this->str, str);
    this->length = length;
}
String::String(int n) {
    capacity = 2;
    char buffer[10];
    _itoa(n, buffer, 10);
    length = strlen(buffer);
    str = new char[length + 1 + capacity];
    str[length] = '\0';
    strcpy(str, buffer);
}
String::String(const String& string) {
    copyFrom(string);
}
String::String(String&& other) noexcept{

    moveFrom(std::move(other));
}
String& String::operator=(String&& other) noexcept{
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}
String& String::operator =(const String& string) {
    if (this != &string) {
        free();
        copyFrom(string);
    }
    return *this;
}



int String::compareTo(const String& string) const {
    for (int i = 0; i < length && i < string.length; i++) {
        if (str[i] < string.str[i]) return -1;
        else if (str[i] > string.str[i]) return 1;
    }
    if (length > string.length) return 1;
    if (length < string.length) return -1;
    return 0;
}

String String::concat(const String& string) const {
    char* ptr = new char[length + string.length + 1];
    strcpy(ptr, this->str);
    strcpy(ptr + length, string.str);
    String concatenatedString(ptr);
    delete[] ptr;
    return concatenatedString;
}

Array<String> String::split(const String& separator) const {
    Array<String> list;
    int startIndex = 0;
    for (int i = 0; i < length; i++) {
        if (isPrefix(str + i, separator.c_str())) {
            if (startIndex != i) list.Add(subStr(startIndex, i));
            startIndex = i + separator.getLength();
            i += separator.getLength() - 1;
        }
    }
    if (startIndex != length) list.Add(subStr(startIndex, length));
    return list;
}
String String::subStr(int startIndex, int endIndex) const {
    if (endIndex != -1 && startIndex > endIndex)
        throw String("StartIndex should be less than endIndex");
    if (endIndex >= length || endIndex == -1) endIndex = length;
    if (endIndex < 0)
        throw String("EndIndex is less than zero!");
    char* data = new char[endIndex - startIndex + 1];
    for (int i = startIndex; i < endIndex; i++)
        data[i - startIndex] = str[i];
    data[endIndex - startIndex] = '\0';
    String res(data);
    delete[] data;
    return res;
}

String String::replace(const String& toReplace, const String& whatToReplace) const {
    String res;
    int iter = 0;
    while (iter < length) {
        if (!isPrefix(str + iter, toReplace.c_str())) {
            char buffer[2];
            buffer[0] = str[iter++];
            buffer[1] = '\0';
            res += buffer;
        }
        else {
            res += whatToReplace;
            iter += toReplace.length;
        }
    }
    return res;
}

String String::operator +(const String& string) {
    String copy(*this);
    copy += string;
    return copy;
}

void String::operator +=(const String& string) {
    if (capacity <= length + string.length)
        resize();
    strcpy(str + length, string.str);
    this->length = length + string.length;
}
void String::operator +=(char c) {
    if (capacity == length + 1) resize();
    str[length++] = c;
    str[length] = '\0';
}
const char& String::operator[](int index) const
{
    return str[index]; // no security check!!
}
int String::my_atoi(const String& myString) {
    int result = 0;
    int sign = 1;//atoi must transform negatives too but for the tast it wont be necessary
    size_t i = 0;

    // Check for optional sign
    if (i < myString.length && (myString.str[i] == '-' || myString.str[i] == '+')) {
        if (myString.str[i] == '-') {
            sign = -1;
        }
        i++;
    }

    while (i < myString.getLength()) {
        result = result * 10 + (myString.str[i] - '0');
        i++;
    }
    return sign * result;
}
char& String::operator[](int index)
{
    return str[index]; // no security check!!
}
ostream& operator <<(ostream& file, const String& string) {
    file << string.str;
    return file;
}
std::istream& operator >>(std::istream& is, String& string) {
    char line[1024];
    std::cin.getline(line, 1024);
    string = line;
    return is;
}
bool String::Starts(const String& string) const {
    for (int i = 0; i < string.length; i++) {
        if (str[i] != string.str[i]) return false;
    }
    return true;
}



bool String::contains(const String& string) const {
    for (int i = 0; i < length - string.length + 1; i++) {
        if (isPrefix(str + i, string.str)) return true;
    }
    return false;
}

bool String::equals(const String& string) const {
    return this->compareTo(string) == 0;
}

int String::IndexOf(const String& string) const {
    for (int i = 0; i < length - string.length + 1; i++) {
        if (isPrefix(str + i, string.str)) return i;
    }
    return -1;
}

bool String::Ends(const String& string) const {
    return IndexOf(string) == length - string.length;
}

bool String::isEmpty() const {
    return length == 0;
}

bool isLowerCase(char c) {
    return c >= 'a' && c <= 'z';
}

bool isUpperCase(char c) {
    return c >= 'A' && c <= 'Z';
}

String String::toUpperCase() const {
    String string = *this;
    for (int i = 0; i < string.length; i++) {
        if (isLowerCase(string.str[i])) {
            string.str[i] = 'A' + string.str[i] - 'a';
        }
    }
    return string;
}


const char* String::c_str() const {
    return str;
}

String String::trim() const {
    int index = 0;
    for (int i = length - 1; i >= 0; i--) {
        if (str[i] != ' ') {
            index = i + 1;
            break;
        }
    }
    return subStr(0, index);
}

int String::getLength() const {
    return length;
}

bool String::operator==(const String& other) const {
    return this->equals(other);
}
bool String::operator!=(const String& other) const {
    return !this->equals(other);
}
bool String::operator<(const String& other) const {
    return this->compareTo(other) < 0;
}
bool String::operator>(const String& other) const {
    return this->compareTo(other) > 0;
}
bool String::operator<=(const String& other) const {
    return this->compareTo(other) <= 0;
}
bool String::operator>=(const String& other) const {
    return this->compareTo(other) >= 0;
}
int getIntLength(int number) {
    if (number == 0) return 1; // Handle the case when number is 0
    int length = 0;
    int temp = number;
    while (temp != 0) {
        temp /= 10;
        ++length;
    }
    return length;
}

String String:: IntToString(int number) {
    int length = getIntLength(number);
    char* buffer = new char[length + 1]; // +1 for null terminator

    bool isNegative = number < 0;
    if (isNegative) number = -number;
    for (int i = length - 1; i >= 0; --i) {
        buffer[i] = '0' + (number % 10);
        number /= 10;
    }

    if (isNegative) buffer[0] = '-';

    buffer[length] = '\0'; // Null-terminate the string

    String result(buffer);

    delete[] buffer; // Clean up allocated memory

    return result;
}
String::~String() {
    free();
}