#include "MyString.h"

#include <cstring>
#include <iostream>
#include <string>

MyString::MyString() : data(new char[1]), length(0) {
    data[0] = '\0';
}

MyString::MyString(const char* str) {
    length = std::strlen(str);
    data = new char[length + 1];
    std::strcpy(data, str);
}

MyString::MyString(const MyString& other) : length(other.length) {
    data = new char[length + 1];
    std::strcpy(data, other.data);
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        delete[] data;
        length = other.length;
        data = new char[length + 1];
        std::strcpy(data, other.data);
    }
    return *this;
}

MyString::~MyString() {
    delete[] data;
}

std::size_t MyString::size() const { return length; }
bool MyString::empty() const { return length == 0; }
const char* MyString::c_str() const { return data; }

char& MyString::operator[](std::size_t index) {
    return data[index];
}

const char& MyString::operator[](std::size_t index) const {
    return data[index];
}

MyString& MyString::operator+=(const MyString& other) {
    std::size_t newLength = length + other.length;
    char* newData = new char[newLength + 1];
    std::strcpy(newData, data);
    std::strcat(newData, other.data);
    delete[] data;
    data = newData;
    length = newLength;
    return *this;
}

bool MyString::operator==(const MyString& other) const {
    return std::strcmp(data, other.data) == 0;
}

bool MyString::operator!=(const MyString& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const MyString& s) {
    os << s.data;
    return os;
}

std::istream& operator>>(std::istream& is, MyString& s) {
    std::string buffer;
    is >> buffer;
    s = MyString(buffer.c_str());
    return is;
}
