#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <cstddef>
#include <utility>
    
template <typename T>
class allocator
{
public:
    using value_type = T;

    T* allocate(std::size_t n);
    
    template <typename... Args>
    void construct(T* p, Args&&... args);

    void destroy(T* p);
    void deallocate(T* p, std::size_t n);
};

#include "allocator_impl.hpp"

#endif // ALLOCATOR_HPP
