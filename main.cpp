#include <iostream>

#include "test_util.h"
#include "test_allocator.h"
#include "test_functional.h"
#include "test_iterator.h"
#include "test_vector.h"

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

void test_func() {
    std::cout << "测试mystl::alloc" << std::endl;
    test_functional_00();
    test_functional_01();
    test_functional_02();
    test_functional_03();
    test_functional_04();
    test_functional_05();
}

void test_iter() {
    test_iterator_01();
    test_iterator_02();
    test_iterator_03();
}

void test_vector() {
    test_vector_01();
    test_vector_02();
}

int main() {
    test_vector();
    return 0;
}