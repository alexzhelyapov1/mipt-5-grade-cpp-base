#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>

class Vector
{
    int* m_data = nullptr;
    std::size_t m_size = 0;
    std::size_t m_capacity = 0;

public:
    ~Vector()
    {
        delete[] m_data;
    }

    [[nodiscard]] std::size_t size() const
    {
        return m_size;
    }

    [[nodiscard]] std::size_t capacity() const
    {
        return m_capacity;
    }

    [[nodiscard]] bool empty() const
    {
        return m_size == 0;
    }

    void clear()
    {
        m_size = 0;
    }

    void push_back(int value)
    {
        if (m_size == m_capacity)
        {
            auto new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
            auto new_data = new int[new_capacity];

            for (std::size_t i = 0; i < m_size; ++i)
            {
                new_data[i] = m_data[i];
            }

            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
        }

        m_data[m_size++] = value;
    }

    int& operator[](std::size_t index)
    {
        return m_data[index];
    }

    const int& operator[](std::size_t index) const
    {
        return m_data[index];
    }
};

int main()
{
    Vector v;

    assert(v.empty());
    assert(v.size() == 0);
    assert(v.capacity() == 0);

    v.push_back(10);
    assert(v.size() == 1);
    assert(v.capacity() == 1);
    assert(v[0] == 10);

    v.push_back(20);
    assert(v.size() == 2);
    assert(v.capacity() == 2);
    assert(v[1] == 20);

    v.push_back(30);
    assert(v.size() == 3);
    assert(v.capacity() == 4);

    v.clear();
    assert(v.empty());
    assert(v.size() == 0);
    assert(v.capacity() == 4);

    v.push_back(40);
    assert(v[0] == 40);
}