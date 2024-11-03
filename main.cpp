#include "allocator_test.hpp"
#include "vector_test.hpp"
#include "vector.hpp"
#include "merge_sort.hpp"

int main() 
{

    test_vector_constructors();
    test_copy_and_move();
    test_push_pop_operations();
    test_iterator();

    Vector<int> vec = {5, 25, 13, 85, 56};
    merge_sort<int>(vec.begin(), vec.end() - 1);

    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}