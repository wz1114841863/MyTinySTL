#include <iostream>
#include <string>
#include "allocator.h"

void test_alloc_01() {
    // 基本类型的创建
    typedef mystl::allocator<std::string> alloc;
    int n = 5;
    auto const startLoc = alloc::allocate(n);
    auto loc = startLoc;
    alloc::construct(loc++);
    alloc::construct(loc++, 10, 'c');
    alloc::construct(loc++, "hi");

    std::cout << *startLoc << std::endl;
    std::cout << startLoc[0] << std::endl;
    std::cout << startLoc[1] << std::endl;
    std::cout << startLoc[2] << std::endl;

    while (startLoc != loc) {
        alloc::destroy(--loc);
    }

    alloc::deallocate(startLoc, n);
}
