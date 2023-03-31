#include <iostream>
#include <vector>
#include "hashtable.h"
#include "unordered_map.h"
#include "unordered_set.h"

void test_hashtable_01() {
    std::cout << "test hash table node: " << std::endl;
    mystl::hashtable_node<int> node1;
    mystl::hashtable_node<int> node2(10);
    mystl::hashtable_node<int> node3(node2);
    mystl::hashtable_node<int> node4(std::move(node3));

    std::cout << "test hash table value traits: " << std::endl;
    std::cout << "get_key："   << mystl::ht_value_traits_imp<int, false>::get_key(100)   << std::endl;
    std::cout << "get_value：" << mystl::ht_value_traits_imp<int, false>::get_value(100) << std::endl;

    mystl::pair<int, int> pair1(10, 100);
    std::cout << "get_key："   << mystl::ht_value_traits_imp<mystl::pair<int, int>, true>::get_key(pair1) << std::endl;
    std::cout << "get_value：" << mystl::ht_value_traits_imp<
            mystl::pair<int, int>, true>::get_value(pair1).second << std::endl;

    std::cout << "get_key："   << mystl::ht_value_traits<int>::get_key(100)   << std::endl;
    std::cout << "get_value：" << mystl::ht_value_traits<int>::get_value(100) << std::endl;
    std::cout << "get_key："   << mystl::ht_value_traits<mystl::pair<int, int>>::get_key(pair1)          << std::endl;
    std::cout << "get_value：" << mystl::ht_value_traits<mystl::pair<int, int>>::get_value(pair1).second << std::endl;
}

void test_hashtable_02() {
    std::cout << "test unrdered_set node: " << std::endl;
    mystl::unordered_set<int> uset1();
    mystl::unordered_set<int> uset2(10);
    mystl::unordered_set<int> uset3(10, mystl::hash<int>(), mystl::equal_to<int>());
    mystl::vector<int> vec1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    mystl::unordered_set<int> uset4(vec1.begin(), vec1.end());
    mystl::unordered_set<int> uset5({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    mystl::unordered_set<int> uset6(uset4);
    mystl::unordered_set<int> uset7(mystl::move(uset6));

    mystl::unordered_set<int> uset8;
    uset8 = uset7;

    mystl::unordered_set<int> uset9;
    uset9 = std::move(uset7);

    mystl::unordered_set<int> uset10;
    uset10 = {1, 2, 3, 4};
}

void test_hashtable_03() {

}
