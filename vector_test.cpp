#include "vector.hpp"
#include "vector_test.hpp"

#include <iostream>
#include <cassert>

void test_vector_constructors()
{
    // Default ctor
    Vector<int> vec1;
    assert(vec1.size() == 0);
    assert(vec1.capacity() == 0);
    std::cout << "Default constructor test passed.\n";

    // ctor with param
    Vector<int> vec2(5);
    assert(vec2.size() == 5);
    std::cout << "Constructor with size test passed.\n";

    // Initializer list ctor
    Vector<int> vec3{1, 2, 3, 4, 5};
    assert(vec3.size() == 5);
    assert(vec3[0] == 1 && vec3[4] == 5);
    std::cout << "Initializer list constructor test passed.\n";
}

void test_copy_and_move()
{
    // Copy ctor
    Vector<int> vec1{1, 2, 3};
    Vector<int> vec2 = vec1;
    assert(vec2.size() == 3 && vec2[0] == 1 && vec2[2] == 3);
    std::cout << "Copy constructor test passed.\n";

    // Move ctor
    Vector<int> vec3 = std::move(vec1);
    assert(vec3.size() == 3 && vec3[0] == 1 && vec3[2] == 3);
    std::cout << "Move constructor test passed.\n";

    // Move assignment
    Vector<int> vec4;
    vec4 = std::move(vec2);
    assert(vec4.size() == 3 && vec4[0] == 1 && vec4[2] == 3);
    std::cout << "Move assignment test passed.\n";
}

void test_push_pop_operations()
{
    Vector<int> vec;

    // Test push_back
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    assert(vec.size() == 3);
    assert(vec[0] == 10 && vec[2] == 30);
    std::cout << "push_back test passed.\n";

    // Test pop_back
    vec.pop_back();
    assert(vec.size() == 2);
    std::cout << "pop_back test passed.\n";
}

void test_iterator()
{
    Vector<int> vec{1, 2, 3, 4, 5};

    int value = 1;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        assert(*it == value);
        ++value;
    }
    std::cout << "Iterator test passed.\n";
}
