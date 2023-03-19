#include <iostream>
#include "algorithm.h"
#include "vector.h"
#include "functional.h"

void test_algorithm_01() {
    std::cout << "test numeric.h" << std::endl;
    std::cout << "test accumulate" << std::endl;
    mystl::vector<int> iv{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << mystl::accumulate(iv.begin(), iv.end(), 11) << std::endl;
    std::cout << mystl::accumulate(iv.begin(), iv.end(), 11,
                                   mystl::plus<int>())  << std::endl;

    std::cout << "test adjacent_difference" << std::endl;
    mystl::vector<int> vec1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    mystl::vector<int> vec2(10, 0), vec3(10, 0);
    mystl::adjacent_difference(vec1.begin(), vec1.end(), vec2.begin());
    mystl::adjacent_difference(vec1.begin(), vec1.end(), vec3.begin(), mystl::minus<int>());
    for (int i = 0; i < 10; ++i) {
        std::cout << vec2[i] << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << vec3[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "test inner_product" << std::endl;
    std::cout << mystl::inner_product(vec1.begin(), vec1.end(), vec2.begin(), 10) << std::endl;
    std::cout << mystl::inner_product(vec1.begin(), vec1.end(), vec2.begin(), 10,
                                      mystl::plus<int>(), mystl::multiplies<int>()) << std::endl;

    std::cout << "test itoa" << std::endl;
    mystl::itoa(vec3.begin(), vec3.end(), 100);
    for (int i = 0; i < 10; ++i) {
        std::cout << vec3[i] << " ";
    }
    std::cout << std::endl;


    std::cout << "test partial_sum" << std::endl;
    mystl::partial_sum(vec3.begin(), vec3.end(), vec2.begin());
    for (int i = 0; i < 10; ++i) {
        std::cout << vec2[i] << " ";
    }
    std::cout << std::endl;
    mystl::partial_sum(vec3.begin(), vec3.end(), vec2.begin(),
                       mystl::plus<int>());
    for (int i = 0; i < 10; ++i) {
        std::cout << vec2[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "test pow" << std::endl;
    std::cout << mystl::pow(10, 2) << std::endl;
    std::cout << mystl::pow(2, 10) << std::endl;
}

void test_algorithm_02() {
    std::cout << "test set" << std::endl;
    std::cout << "test S1 U S2" << std::endl;
    mystl::vector<int> vec1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    mystl::vector<int> vec2{2, 4, 6, 7, 11, 12, 14};
    mystl::vector<int> vec3(30);
    mystl::set_union(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), vec3.begin());
    for (int num : vec3) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    mystl::set_union(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), vec3.begin(),
                     mystl::less<int>());
    for (int num : vec3) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    mystl::vector<int> vec4(30);
    std::cout << "test S1 ∩ S2" << std::endl;
    mystl::set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), vec4.begin());
    for (int num : vec4) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    mystl::set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), vec4.begin(),
                     mystl::less<int>());
    for (int num : vec4) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    mystl::vector<int> vec5(30);
    std::cout << "test S1 - S2" << std::endl;
    mystl::set_difference(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), vec5.begin());
    for (int num : vec5) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    mystl::set_difference(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), vec5.begin(),
                            mystl::less<int>());
    for (int num : vec5) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    mystl::vector<int> vec6(30);
    std::cout << "test (S1 - S2) ∪ (S2 - S1)" << std::endl;
    mystl::set_symmetric_difference(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), vec6.begin());
    for (int num : vec6) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    mystl::set_symmetric_difference(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), vec6.begin(),
                          mystl::less<int>());
    for (int num : vec6) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void printVec(const mystl::vector<T> &vec1) {
    for (int i = 0; i < vec1.size(); ++i) {
        std::cout << vec1[i] << " ";
    }
    std::cout << std::endl;
}

void test_algorithm_03() {
    std::cout << "test heap alog: " << std::endl;
    mystl::vector<int> vec1{3, 4, 5 ,2, 1, 9, 7, 8, 0};
    std::cout << "test make_heap: " << std::endl;
    mystl::make_heap(vec1.begin(), vec1.end());
    printVec(vec1);
    std::cout << "test push_heap: " << std::endl;
    vec1.push_back(10);
    mystl::push_heap(vec1.begin(), vec1.end());
    printVec(vec1);
    vec1.push_back(6);
    mystl::push_heap(vec1.begin(), vec1.end());
    printVec(vec1);
    std::cout << "test pop_heap: " << std::endl;
    mystl::pop_heap(vec1.begin(), vec1.end());
    printVec(vec1);
    std::cout << "test sort_heap: " << std::endl;
    mystl::sort_heap(vec1.begin(), vec1.end() - 1);
    printVec(vec1);

    vec1 = {3, 4, 5 ,2, 1, 9, 7, 8, 0};
    std::cout << "test make_heap: " << std::endl;
    mystl::make_heap(vec1.begin(), vec1.end(), mystl::less<int>());
    printVec(vec1);
    std::cout << "test push_heap: " << std::endl;
    vec1.push_back(10);
    mystl::push_heap(vec1.begin(), vec1.end(), mystl::less<int>());
    printVec(vec1);
    vec1.push_back(6);
    mystl::push_heap(vec1.begin(), vec1.end(), mystl::less<int>());
    printVec(vec1);
    std::cout << "test pop_heap: " << std::endl;
    mystl::pop_heap(vec1.begin(), vec1.end(), mystl::less<int>());
    printVec(vec1);
    std::cout << "test sort_heap: " << std::endl;
    mystl::sort_heap(vec1.begin(), vec1.end() - 1, mystl::less<int>());
    printVec(vec1);
}

bool judge(int val) {
    return val > 3 ? true : false;
}

void test_algorithm_04() {
    std::cout << "test algo_base" << std::endl;
    std::cout << "max" << std::endl;
    std::cout << "max(10, 20): " << mystl::max(10, 20) << std::endl;
    std::cout << "min" << std::endl;
    std::cout << "min(10, 20): " << mystl::min(10, 20) << std::endl;
    std::cout << "iter_swap" << std::endl;
    // 不能取常数的地址
    int num1 = 100, num2 = 200;
    int *val1 = &num1, *val2 = &num2;
    std::cout << "iter_swap before" << "val1: " << *val1 << "val2: " << *val2 << std::endl;
    mystl::iter_swap(val1, val2);
    std::cout << "iter_swap after" << "val1: " << *val1 << "val2: " << *val2 << std::endl;

    mystl::vector<int> vec1{1, 2, 3, 5, 6, 9};
    mystl::vector<int> vec2(6, 0), vec3(6, 0);
    std::cout << "copy" << std::endl;
    mystl::copy(vec1.begin(), vec1.end(), vec2.begin());
    printVec(vec2);
    std::cout << "copy_backward" << std::endl;
    mystl::copy_backward(vec1.begin(), vec1.end(), vec3.end());
    printVec(vec3);
    std::cout << "copy_if" << std::endl;
    mystl::vector<int> vec4(6, 0);
    printVec(vec1);
    mystl::copy_if(vec1.begin(), vec1.end(), vec4.begin(), judge);
    printVec(vec4);
    std::cout << "copy_n" << std::endl;
    mystl::vector<int> vec5(4, 0);
    mystl::copy_n(vec1.begin(), 4, vec5.begin());
    printVec(vec5);
    std::cout << "move" << std::endl;
    std::cout << "move int" << std::endl;
    mystl::vector<int> vec6(6, 0);
    mystl::move(vec1.begin(), vec1.end(), vec6.begin());
    printVec(vec1);
    printVec(vec6);
    std::cout << "move string" << std::endl;
    mystl::vector<std::string> vecStr1{"aa", "bb", "cc"};
    mystl::vector<std::string> vecStr2(3);
    printVec(vecStr1);
    mystl::move(vecStr1.begin(), vecStr1.end(), vecStr2.begin());
    printVec(vecStr1);
    printVec(vecStr2);
    std::cout << "move string backward" << std::endl;
    mystl::vector<std::string> vecStr3{"aa", "bb", "cc"};
    mystl::vector<std::string> vecStr4(3);
    printVec(vecStr3);
    mystl::move_backward(vecStr3.begin(), vecStr3.end(), vecStr4.end());
    printVec(vecStr3);
    printVec(vecStr4);
    std::cout << "equal: " << std::endl;
    std::cout << "vec1 equal vec2: " << mystl::equal(vec1.begin(), vec1.end(),
                                                     vec6.begin()) << std::endl;
    std::cout << "fill" << std::endl;
    mystl::vector<std::string> vecStr5(10);
    mystl::fill(vecStr5.begin(), vecStr5.end(), "aa");
    printVec(vecStr5);
    std::cout << "fill_n" << std::endl;
    mystl::vector<std::string> vecStr6(10);
    mystl::fill_n(vecStr6.begin(), 10, "bb");
    printVec(vecStr6);
    std::cout << "mismatch: " << std::endl;
    vecStr6 = vecStr5;
    vecStr6[4] = "bb";
    auto tmp = mystl::mismatch(vecStr5.begin(), vecStr5.end(),
                               vecStr6.begin());
    printVec(vecStr5);
    printVec(vecStr6);
    std::cout << "tmp.fisrt: "  << *tmp.first  << std::endl;
    std::cout << "tmp.second: " << *tmp.second << std::endl;
}