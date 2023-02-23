#include <iostream>

#include "util_test.cpp"
#include "allocator_test.cpp"

void test_utils() {
    // 测试utils.h中定义的: move, forward, swap, pair
    test_move();
    test_move_1();
    test_forward();
    test_swap();
    test_pair();
}

void test_alloc() {
    std::cout << "测试mystl::alloc" << std::endl;
    test_alloc_01();
    test_alloc_02();
}

int main() {
    test_alloc();
    test_utils();
    return 0;
}