#include <iostream>
#include "./MyTinySTL/utils/util.h"

#include "./Test/utils_test.h"

int main() {

    return 0;
}

void test_utils() {
    // 测试utils.h中定义的: move, forward, swap, pair
    test_move();
    test_move_1();
    test_forward();
    test_swap();
    test_pair();
}

