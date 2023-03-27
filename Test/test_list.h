#include <iostream>
#include <string>
#include <typeinfo>
#include "iterator.h"
#include "list.h"
#include "vector.h"


// void test_list_01() {
//     std::cout << "测试 构造函数" << std::endl;
//     mystl::list<int> list1;
//     std::cout << "list1.size():" << list1.size() << std::endl;
//
//     mystl::list<int> list2(50);
//     std::cout << "list2.size():" << list2.size() << std::endl;
//
//     mystl::list<std::string> list3(30, "aa");
//     std::cout << "list3.size():" << list3.size() << std::endl;
//
//     mystl::vector<int> vec1{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
//     mystl::list<int> list4(vec1.begin(), vec1.end());
//     std::cout << "list4.size():" << list4.size() << std::endl;
//
//     mystl::list<std::string> list5(list3);
//     std::cout << "list5.size():" << list5.size() << std::endl;
//
//     mystl::list<std::string> list6(mystl::move(list3));
//     std::cout << "list3.size():" << list3.size() << std::endl;
//     std::cout << "list6.size():" << list6.size() << std::endl;
//
//     mystl::list<int> list7;
//     list7 = list1;
//     std::cout << "list7.size():" << list7.size() << std::endl;
//
//     mystl::list<std::string> list8;
//     list8 = mystl::move(list6);
//     std::cout << "list8.size():" << list8.size() << std::endl;
//     std::cout << "list6.size():" << list6.size() << std::endl;
//
//     mystl::list<int> list9;
//     list9 = {1, 2, 3, 5, 6, 7};
//     std::cout << "list9.size():" << list9.size() << std::endl;
// }