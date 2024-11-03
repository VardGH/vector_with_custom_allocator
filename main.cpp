#include "allocator_test.hpp"
#include "vector_test.hpp"

int main() 
{

    test_vector_constructors();
    test_copy_and_move();
    test_push_pop_operations();
    test_iterator();

    return 0;
}
