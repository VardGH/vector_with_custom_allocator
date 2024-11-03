#include "vector.hpp"
#include <algorithm>
#include <memory>
#include <utility>

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector()
    : m_data(nullptr)
    , m_size(0), m_capacity(0) 
{
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(std::size_t count)
    : m_size(count)
    , m_capacity(count) 
{
    m_data = m_allocator.allocate(m_capacity);

    for (std::size_t i = 0; i < m_size; ++i) {
        m_allocator.construct(m_data + i);
    }
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(std::initializer_list<T> init)
    : m_size(init.size())
    , m_capacity(init.size()) 
{
    m_data = m_allocator.allocate(m_capacity);
    std::uninitialized_copy(init.begin(), init.end(), m_data);
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(const Vector& rhs)
    : m_size(rhs.m_size)
    , m_capacity(rhs.m_capacity) 
{
    m_data = m_allocator.allocate(m_capacity);
    std::uninitialized_copy(rhs.m_data, rhs.m_data + m_size, m_data);
}

template <typename T, typename Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector& rhs)
{
    if (this != &rhs) {
        // Clean up
        for (std::size_t i = 0; i < m_size; ++i)
            m_allocator.destroy(m_data + i);
        m_allocator.deallocate(m_data, m_capacity);

        // Copy new data
        m_size = rhs.m_size;
        m_capacity = rhs.m_capacity;
        m_data = m_allocator.allocate(m_capacity);
        std::uninitialized_copy(rhs.m_data, rhs.m_data + m_size, m_data);
    }
    return *this;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(Vector&& rhs) noexcept
    : m_data(rhs.m_data)
    , m_size(rhs.m_size)
    , m_capacity(rhs.m_capacity) 
{
    rhs.m_data = nullptr;
    rhs.m_size = 0;
    rhs.m_capacity = 0;
}

template <typename T, typename Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(Vector&& rhs) noexcept
{
    if (this != &rhs) {
        // Clean up
        for (std::size_t i = 0; i < m_size; ++i) {
            m_allocator.destroy(m_data + i);
        }
        m_allocator.deallocate(m_data, m_capacity);

        m_data = rhs.m_data;
        m_size = rhs.m_size;
        m_capacity = rhs.m_capacity;

        // Reset rhs
        rhs.m_data = nullptr;
        rhs.m_size = 0;
        rhs.m_capacity = 0;
    }
    return *this;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::~Vector()
{
    for (std::size_t i = 0; i < m_size; ++i) {
        m_allocator.destroy(m_data + i);
    }
    m_allocator.deallocate(m_data, m_capacity);
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::reallocate(std::size_t new_capacity)
{
    T* new_data = m_allocator.allocate(new_capacity);
    for (std::size_t i = 0; i < m_size; ++i) {
        m_allocator.construct(new_data + i, std::move(m_data[i]));
        m_allocator.destroy(m_data + i);
    }
    m_allocator.deallocate(m_data, m_capacity);

    m_data = new_data;
    m_capacity = new_capacity;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::push_back(const T& value)
{
    if (m_size == m_capacity) {
        reallocate(m_capacity == 0 ? 1 : m_capacity * 2);
    }
    m_allocator.construct(m_data + m_size, value);
    ++m_size;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::pop_back()
{
    if (m_size > 0) {
        --m_size;
        m_allocator.destroy(m_data + m_size);
    }
}

template <typename T, typename Allocator>
T& Vector<T, Allocator>::operator[](std::size_t index)
{
    if (index >= m_size) {
        throw std::out_of_range("Index out of bounds");
    }

    return m_data[index];
}

template <typename T, typename Allocator>
const T& Vector<T, Allocator>::operator[](std::size_t index) const
{
    if (index >= m_size) {
        throw std::out_of_range("Index out of bounds");
    }

    return m_data[index];
}

template <typename T, typename Allocator>
std::size_t Vector<T, Allocator>::size() const noexcept
{
    return m_size;
}

template <typename T, typename Allocator>
std::size_t Vector<T, Allocator>::capacity() const noexcept
{
    return m_capacity;
}