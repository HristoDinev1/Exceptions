#pragma once
#include <cstddef>

namespace banking
{
    template<typename T>
    class MyVector
    {
    private:
        T* data;
        size_t count;
        size_t capacity;

        void resize(size_t newCapacity)
        {
            T* newData = new T[newCapacity];

            for (size_t i = 0; i < count; i++)
            {
                newData[i] = data[i];
            }

            delete[] data;
            data = newData;
            capacity = newCapacity;
        }

    public:
        MyVector()
        {
            capacity = 4;
            count = 0;
            data = new T[capacity];
        }

        ~MyVector()
        {
            delete[] data;
        }

        void pushBack(const T& value)
        {
            if (count >= capacity)
            {
                resize(capacity * 2);
            }

            data[count++] = value;
        }

        T& operator[](size_t index)
        {
            return data[index];
        }

        const T& operator[](size_t index) const
        {
            return data[index];
        }

        size_t size() const
        {
            return count;
        }
    };
}
