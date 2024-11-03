#ifndef ALLOCATOR_IMPL_HPP
#define ALLOCATOR_IMPL_HPP

#include <iostream>
#include <new>

template <typename T>
T* allocator<T>::allocate(std::size_t n) 
{
    std::cout << "allocate " << n << std::endl;
    return static_cast<T*>(::operator new(n * sizeof(T))); // global operator new function, which is a low-level memory allocation function
}

template <typename T>
template <typename... Args>
void allocator<T>::construct(T* p, Args&&... args) 
{
    std::cout << "construct " << std::endl;
    new (p) T(std::forward<Args>(args)...); // construct object in allocated memory
}

template <typename T>
void allocator<T>::destroy(T* p) 
{
    std::cout << "destroy " << std::endl;
    p->~T(); // explicitly call the dtor
}

template <typename T>
void allocator<T>::deallocate(T* p, std::size_t n) 
{
    std::cout << "deallocate " << n << std::endl;
    ::operator delete(p); /// deallocate raw memory
}

#endif // ALLOCATOR_IMPL_HPP