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

void test_algorithm_03() {

}

void test_algorithm_04() {

}