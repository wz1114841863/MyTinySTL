#ifndef TINYSTL_UTIL_H
#define TINYSTL_UTIL_H

// 通用工具头文件：move, forward, swap, pair...
#include <cstddef>
#include "type_traits.h"

namespace mystl {
    // move: 不管传入的是左值还是右值，最终转换为右值
    /*  输入参数类型为通用引用类型，既可以接收左值，也可以接收右值
     *  通用应用的成立条件: 一种是auto，一种是 T &&, 实际上 auto == T
     */
    template <typename T>
    typename std::remove_reference<T>::type &&move(T &&arg) noexcept {
        return static_cast<typename std::remove_reference<T>::type &&>(arg);
    }

    // forward:
    /*
     * 完美转发：通过函数转发保证参数的左值/右值，const/non-const属性不变。
     * 引用折叠：X& &，X& && 和 X&& & 折叠成X&， X&& &&折叠成X&&
     */
    template <class T>
    T&& forward(typename std::remove_reference<T>::type &arg) noexcept {
        return static_cast<T &&>(arg);
    }

    template <class T>
    T&& forward(typename std::remove_reference<T>::type &&arg) noexcept {
        static_assert(!std::is_lvalue_reference<T>::value, "bad forward");
        return static_cast<T &&>(arg);
    }

    // swap: 借助 move 移动语义，对复杂的数据无需进行大量的复制操作
    template <class Tp>
    void swap(Tp &lhs, Tp &rhs) {
        auto tmp(mystl::move(lhs));
        lhs = mystl::move(rhs);
        rhs = mystl::move(tmp);
    }

    template <typename ForwardIter1, typename ForwardIter2>
    ForwardIter2 swap_range(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2) {
        for (; first1 != last1; ++first1, (void) ++first2) {
            mystl::swap(*first1, *first2);
            return first2;
        }
    }

    template <typename Tp, size_t N>
    void swap(Tp(&a)[N], Tp(&b)[N]) {
        mystl::swap_range(a, a + N, b);
    }
}

#endif //TINYSTL_UTIL_H
