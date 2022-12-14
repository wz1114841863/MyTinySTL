#ifndef TINYSTL_UTILS_TEST_H
#define TINYSTL_UTILS_TEST_H

#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>
#include <utility>
#include "../MyTinySTL/utils/util.h"

int gettimeofday(struct timeval *tp)
{
    time_t clock;
    struct tm tm1;
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    tm1.tm_year = wtm.wYear - 1900;
    tm1.tm_mon = wtm.wMonth - 1;
    tm1.tm_mday = wtm.wDay;
    tm1.tm_hour = wtm.wHour;
    tm1.tm_min = wtm.wMinute;
    tm1.tm_sec = wtm.wSecond;
    tm1. tm_isdst = -1;
    clock = mktime(&tm1);
    tp->tv_sec = clock;
    tp->tv_usec = wtm.wMilliseconds * 1000;
    return (0);
}

void test_move() {
    std::cout << "move 功能测试..." << std::endl;
    // 定义左值
    std::string st1 = "test1", st2;
    std::cout << "直接将 st1 赋值给 st2:          " << std::endl;
    st2 = st1;
    std::cout << "st1: " << st1 << " st2: " << st2 << std::endl;

    std::string st3 = "test3", st4;
    std::cout << "使用 std::move 将st3移动到st4:  " << std::endl;
    st4 = std::move(st3);
    std::cout << "st3: " << st3 << " st4: " << st4 << std::endl;

    std::string st5 = "test3", st6;
    std::cout << "使用 mystl::move 将st3移动到st4:" << std::endl;
    st6 = mystl::move(st5);
    std::cout << "st5: " << st5 << " st6: " << st6 << std::endl;
}

void test_move_1() {
    std::cout << "move 性能测试..." << std::endl;
    const int kRunTime = 1000 * 1000;     // 循环次数
    const int kStringLength = 100000;   // 字符串长度
    std::string str;
    std::string copy_str, std_move_str, mystl_move;

    for(int i = 0; i < kStringLength; ++i)
        str += 'a';

    timeval start, end;
    gettimeofday(&start);
    for (int i = 0; i < kRunTime; ++i) {
        copy_str = str;
//        str = copy_str;
    }
    gettimeofday(&end);
    std::cout << "copy string, time: " << (end.tv_sec - start.tv_sec) * 1000
        << (end.tv_usec-start.tv_usec) / 1000 << "ms" << std::endl;

    gettimeofday(&start);
    for (int i = 0; i < kRunTime; ++i) {
        std_move_str = std::move(str);
        str = std::move(std_move_str);
    }
    gettimeofday(&end);
    std::cout << "std move string, time: " << (end.tv_sec - start.tv_sec) * 1000
              << (end.tv_usec-start.tv_usec) / 1000 << "ms" << std::endl;

    gettimeofday(&start);
    for (int i = 0; i < kRunTime; ++i) {
        std_move_str = mystl::move(str);
        str = mystl::move(std_move_str);
    }
    gettimeofday(&end);
    std::cout << "std move string, time: " << (end.tv_sec - start.tv_sec) * 1000
              << (end.tv_usec-start.tv_usec) / 1000 << "ms" << std::endl;
}

// function with lvalue and rvalue reference overloads:
void overloaded(const int& x) {
    std::cout << "[lvalue]: " << x << std::endl;
}

void overloaded(int&& x) {
    std::cout << "[rvalue]: " << x << std::endl;
}

template <class T> void fn (T&& x) {
    overloaded (x);                   // always an lvalue
    overloaded (std::forward<T>(x));  // rvalue if argument is rvalue
}

template <class T> void fn1 (T&& x) {
    overloaded (x);                   // always an lvalue
    overloaded (mystl::forward<T>(x));  // rvalue if argument is rvalue
}

void test_forward() {
    std::cout << "forward 功能测试..." << std::endl;
    int a = 10;
    std::cout << "左值a" << std::endl;
    fn(a);
    fn1(a);
    std::cout << "右值0" << std::endl;
    fn(0);
    fn1(0);
}

void test_swap() {
    std::cout << "swap 函数测试...  " << std::endl;
    int a = 10, b = 20;
    std::cout << "使用std::swap()之前，a: " << a << " b: " << b << std::endl;
    std::swap(a, b);
    std::cout << "使用std::swap()之后，a: " << a << " b: " << b << std::endl;

    std::cout << "使用mystl::swap()之前，a: " << a << " b: " << b << std::endl;
    mystl::swap(a, b);
    std::cout << "使用mystl::swap()之后，a: " << a << " b: " << b << std::endl;

    std::string st1 = "test1.", st2 = "test2";
    std::cout << "使用std::swap()之前，st1: " << st1 << " st2: " << st2 << std::endl;
    std::swap(st1, st2);
    std::cout << "使用std::swap()之后，st1: " << st1 << " st2: " << st2 << std::endl;

    std::cout << "使用mystl::swap()之前，st1: " << st1 << " st2: " << st2 << std::endl;
    mystl::swap(st1, st2);
    std::cout << "使用mystl::swap()之后，st1: " << st1 << " st2: " << st2 << std::endl;
}

void test_pair() {
    // pair 初始化测试
    std::pair<int, int> p1;
    std::cout << "p1.first: " << p1.first << " p1.second: " << p1.second << std::endl;
    std::pair<int, int> p2(10, 20);
    std::cout << "p2.first: " << p2.first << " p2.second: " << p2.second << std::endl;
    std::pair<std::string, std::string> p3;
    std::cout << "p3.first: " << p3.first << " p3.second: " << p3.second << std::endl;
    std::pair<std::string, std::string> p4("abc", "def");
    std::cout << "p4.first: " << p4.first << " p4.second: " << p4.second << std::endl;
    std::pair<int, std::string> p5;
    std::cout << "p5.first: " << p5.first << " p5.second: " << p5.second << std::endl;
    std::pair<std::string, int> p6("xyz", 30);
    std::cout << "p6.first: " << p6.first << " p6.second: " << p6.second << std::endl;

    mystl::pair<int, int> my_p1;
    std::cout << "my_p1.first: " << my_p1.first << " my_p1.second: " << my_p1.second << std::endl;
    mystl::pair<int, int> my_p2(10, 20);
    std::cout << "my_p2.first: " << my_p2.first << " my_p2.second: " << my_p2.second << std::endl;
    mystl::pair<std::string, std::string> my_p3;
    std::cout << "my_p3.first: " << my_p3.first << " my_p3.second: " << my_p3.second << std::endl;
    mystl::pair<std::string, std::string> my_p4("abc", "def");
    std::cout << "my_p4.first: " << my_p4.first << " my_p4.second: " << my_p4.second << std::endl;
    mystl::pair<int, std::string> my_p5;
    std::cout << "my_p5.first: " << my_p5.first << " my_p5.second: " << my_p5.second << std::endl;
    mystl::pair<std::string, int> my_p6("xyz", 30);
    std::cout << "my_p6.first: " << my_p6.first << " my_p6.second: " << my_p6.second << std::endl;

    // test operator
    auto p7 = std::make_pair(50, 60);
    auto my_p7 = mystl::make_pair(50, 70);
    std::cout << "p1 == p7: " << (p1 == p7) << std::endl;
    std::cout << "my_p1 == my_p7: " << (my_p1 == my_p7) << std::endl;
    auto p8 = p2;
    auto my_p8 = my_p2;
    std::cout << "befor swap p7: " << p7.first << "p8: " << p8.first << std::endl;
    std::swap(p7, p8);
    std::cout << "after swap p7: " << p7.first << "p8: " << p8.first << std::endl;

    std::cout << "befor swap my_p7: " << my_p7.first << "my_p8: " << my_p8.first << std::endl;
    mystl::swap(my_p7, my_p8);
    std::cout << "after swap my_p7: " << my_p7.first << "my_p8: " << my_p8.first << std::endl;

}
#endif //TINYSTL_UTILS_TEST_H
