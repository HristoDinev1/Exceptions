#pragma once
#include <cstddef>
#include <iosfwd>

// Simple student-style string class.
// Does NOT defend against bad usage: no bounds checks, no null checks.
class MyString {
private:
    char* data;
    std::size_t length;

public:
    MyString();
    MyString(const char* str);
    MyString(const MyString& other);
    MyString& operator=(const MyString& other);
    ~MyString();

    std::size_t size() const;
    bool empty() const;
    const char* c_str() const;

    // No bounds check.
    char& operator[](std::size_t index);
    const char& operator[](std::size_t index) const;

    MyString& operator+=(const MyString& other);
    bool operator==(const MyString& other) const;
    bool operator!=(const MyString& other) const;

    friend std::ostream& operator<<(std::ostream& os, const MyString& s);
    friend std::istream& operator>>(std::istream& is, MyString& s);
};
