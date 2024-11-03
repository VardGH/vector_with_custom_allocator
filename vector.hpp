#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "allocator.hpp"
#include <initializer_list>

template <typename T, typename Allocator = allocator<T>>
class Vector
{
public:

    // Cotors
    Vector();
    explicit Vector(std::size_t count);
    Vector(std::initializer_list<T> init);
    
    // Copy Semantics
    Vector(const Vector& rhs);
    Vector& operator=(const Vector& rhs);

    // Move Semantics
    Vector(Vector&& rhs) noexcept;
    Vector& operator=(Vector&& rhs) noexcept;

    // Dtor
    ~Vector();

    // Nested iterator class
    class Iterator 
    {
    public:
        // Ctors
        Iterator() : m_ptr(nullptr) {}
        explicit Iterator(T* ptr) : m_ptr(ptr) {}

        // Dereference operators
        T& operator*() const { return *m_ptr; }
        T* operator->() const { return m_ptr; }

        // Pre-increment
        Iterator& operator++() 
        { 
            ++m_ptr; 
            return *this; 
        }

        // Post-increment
        Iterator operator++(int) 
        { 
            Iterator temp = *this;
            ++(*this); 
            return temp; 
        }

        // Pre-decrement
        Iterator& operator--() 
        {
            --m_ptr;
            return *this;
        }

        // Post-decrement
        Iterator operator--(int) 
        {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        // Arithmetic operations
        Iterator operator+(size_t offset) const { return Iterator(m_ptr + offset); }
        Iterator operator-(size_t offset) const { return Iterator(m_ptr - offset); }
        Iterator& operator+=(size_t offset) 
        {
            m_ptr += offset;
            return *this;
        }

        Iterator& operator-=(size_t offset) 
        {
            m_ptr -= offset;
            return *this;
        }

        std::ptrdiff_t operator-(const Iterator& other) const 
        {
            return m_ptr - other.m_ptr;
        }

        // Comparison operators
        bool operator==(const Iterator& other) const { return m_ptr == other.m_ptr; }
        bool operator!=(const Iterator& other) const { return m_ptr != other.m_ptr; }
        bool operator< (const Iterator& other) const { return m_ptr < other.m_ptr;  }
        bool operator<=(const Iterator& other) const { return m_ptr <= other.m_ptr; }
        bool operator> (const Iterator& other) const { return m_ptr > other.m_ptr;  }
        bool operator>=(const Iterator& other) const { return m_ptr >= other.m_ptr; }

    private:
        T* m_ptr;
    };

public:
    void push_back(const T& value);
    void pop_back();
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;

    // Iterator interface
    Iterator begin() { return Iterator(m_data); }
    Iterator end() { return Iterator(m_data + m_size); }

private:
    void reallocate(std::size_t new_capacity);

private:
    Allocator m_allocator;
    T* m_data;
    std::size_t m_size;
    std::size_t m_capacity;
};

#include "vector_impl.hpp"

#endif // VECTOR_HPP
