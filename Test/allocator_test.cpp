#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include "allocator.cpp"

void test_alloc_01() {
    // 基本类型的创建
    std::cout << "基本类型的构建：" << std::endl;
    typedef mystl::allocator<std::string> myalloc;
    int n = 5;
    auto const startLoc = myalloc::allocate(n);
    auto loc = startLoc;
    myalloc::construct(loc++);
    myalloc::construct(loc++, 10, 'c');
    myalloc::construct(loc++, "hi");
    std::cout << startLoc[0] << std::endl;
    std::cout << startLoc[1] << std::endl;
    std::cout << startLoc[2] << std::endl;

    while (startLoc != loc) {
        myalloc::destroy(--loc);
    }

    myalloc::deallocate(startLoc, n);
}

void test_alloc_02() {
    std::cout << "元素的复制与拷贝：" << std::endl;
    // vector 测试
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    typedef mystl::allocator<int> myalloc;
    auto p = myalloc::allocate(vec.size() * 2);
    auto q = std::uninitialized_copy(vec.begin(), vec.end(), p);
    std::uninitialized_fill_n(q, vec.size(), 7);

    for (int i = 0; i < vec.size() * 2; ++i) {
        std::cout << p[i] << " ";
    }
}
