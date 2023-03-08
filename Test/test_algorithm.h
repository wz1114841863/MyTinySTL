#include <iostream>
#include <vector>

#include "algorithm.h"
#include "functional.h"

int test_numeric() {
    // 测试accumulate
    std::vector<int> iv{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::cout << mystl::accumulate(iv.begin(), iv.end(), 0);

    return 0;
}