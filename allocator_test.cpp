#include "allocator_test.hpp"
#include "allocator.hpp"

void alloc_test()
{
    allocator<int> ob;
    std::size_t count = 5;
    int* p = ob.allocate(count);

    for (int i = 0; i < count; ++i) {
        ob.construct(p + i, i + 1);
    }

    for (int i = 0; i < count; ++i) {
        ob.destroy(p + i);
    }

    ob.deallocate(p, count);
}