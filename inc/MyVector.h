#pragma once
#include <cstddef>

// Student-style dynamic array.
// Intentionally without bounds checks, capacity checks, etc.
template <typename T>
class MyVector {
private:
    T* data;
    std::size_t capacity_;
    std::size_t size_;

    void grow() {
        std::size_t newCapacity = (capacity_ == 0) ? 4 : capacity_ * 2;
        T* newData = new T[newCapacity];
        for (std::size_t i = 0; i < size_; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity_ = newCapacity;
    }

public:
    MyVector() : data(nullptr), capacity_(0), size_(0) {}

    MyVector(const MyVector& other)
        : data(nullptr), capacity_(other.capacity_), size_(other.size_) {
        if (capacity_ > 0) {
            data = new T[capacity_];
            for (std::size_t i = 0; i < size_; ++i) {
                data[i] = other.data[i];
            }
        }
    }

    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            delete[] data;
            data = nullptr;
            capacity_ = other.capacity_;
            size_ = other.size_;
            if (capacity_ > 0) {
                data = new T[capacity_];
                for (std::size_t i = 0; i < size_; ++i) {
                    data[i] = other.data[i];
                }
            }
        }
        return *this;
    }

    ~MyVector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            grow();
        }
        data[size_++] = value;
    }

    // No empty-check.
    void pop_back() {
        --size_;
    }

    // No bounds checks.
    T& operator[](std::size_t index)             { return data[index]; }
    const T& operator[](std::size_t index) const { return data[index]; }

    // Same as operator[] for now; students will turn this into a checked version.
    T& at(std::size_t index)             { return data[index]; }
    const T& at(std::size_t index) const { return data[index]; }

    std::size_t size()     const { return size_; }
    std::size_t capacity() const { return capacity_; }
    bool empty()           const { return size_ == 0; }

    // No overflow / length check on requested size.
    void reserve(std::size_t newCapacity) {
        if (newCapacity <= capacity_) return;
        T* newData = new T[newCapacity];
        for (std::size_t i = 0; i < size_; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity_ = newCapacity;
    }

    void clear() {
        size_ = 0;
    }
};
