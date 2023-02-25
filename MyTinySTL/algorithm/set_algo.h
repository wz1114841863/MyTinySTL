#ifndef TINYSTL_SET_ALGO_H
#define TINYSTL_SET_ALGO_H
// 与set有关的四种算法：union、intersection、deifference、symmetric_difference
// 所有序列要求有序
#include "algobase.h"
#include "iterator.h"
namespace mystl {
    /*****************************************************************************************/
    // set_union
    // 计算 S1∪S2 的结果并保存到 result 中，返回一个迭代器指向输出结果的尾部
    /*****************************************************************************************/
    template <typename InputIter1, typename InputIter2, typename OutputIter>
    OutputIter set_union(nputIter1 first1, InputIter1 last1,
                         InputIter2 first2, InputIter2 last2,
                         OutputIter result) {
        while (first1 != last1 && first2 != last2) {
            if (*first1 < *first2) {
                *result = *first1;
                ++first1;
            }else if (*first2 < *first1) {
                *result = *first2;
                ++first2;
            }else {
                *result = *first1;
                ++first1;
                ++first2;
            }
            ++result;
        }

        return mystl::copy(first2, last2, mystl::copy(first1, last1, result))
    }

    template <typename InputIter1, typename InputIter2,
            typename OutputIter, typename Compared>
    OutputIter set_union(nputIter1 first1, InputIter1 last1,
                         InputIter2 first2, InputIter2 last2,
                         OutputIter result, Compared comp) {
        // 前提应该是已经排序
        while (first1 != last1 && first2 != last2) {
            if (comp(*first1, *first2)) {
                *result = *first1;
                ++first1;
            }else if (comp(*first2, *first1)) {
                *result = *first2;
                ++first2;
            }else {
                *result = *first1;
                ++first1;
                ++first2;
            }
            ++result;
        }

        return mystl::copy(first2, last2, mystl::copy(first1, last1, result))
    }

    /*****************************************************************************************/
    // set_intersection
    // 计算 S1∩S2 的结果并保存到 result 中，返回一个迭代器指向输出结果的尾部
    /*****************************************************************************************/
    template <typename InputIter1, typename InputIter2, typename OutputIter>
    OutputIter set_intersection(nputIter1 first1, InputIter1 last1,
                         InputIter2 first2, InputIter2 last2,
                         OutputIter result) {
        while (first1 != last1 && first2 != last2) {
            if (*first1 < *first2) {
                ++first1;
            }else if (*first2 < *first1) {
                ++first2;
            }else {
                *result = *first1;
                ++first1;
                ++first2;
                ++result;
            }
        }

        return result;
    }

    template <typename InputIter1, typename InputIter2,
            typename OutputIter, typename Compared>
    OutputIter set_intersection(nputIter1 first1, InputIter1 last1,
                                InputIter2 first2, InputIter2 last2,
                                OutputIter result, Compared comp) {
        while (first1 != last1 && first2 != last2) {
            if (comp(*first1, *first2)) {
                ++first1;
            }else if (comp(*first2, *first1)) {
                ++first2;
            }else {
                *result = *first1;
                ++first1;
                ++first2;
                ++result;
            }
        }

        return result;
    }

    /*****************************************************************************************/
    // set_difference
    // 计算 S1-S2 的结果并保存到 result 中，返回一个迭代器指向输出结果的尾部
    /*****************************************************************************************/
    template <typename InputIter1, typename InputIter2, typename OutputIter>
    OutputIter set_difference(nputIter1 first1, InputIter1 last1,
                                InputIter2 first2, InputIter2 last2,
                                OutputIter result) {
        while (first1 != last1 && first2 != last2) {
            if (*first1 < *first2) {
                *result = *first1;
                ++first1;
                ++result;
            }else if (*first2 < *first1) {
                ++first2;
            }else {
                ++first1;
                ++first2;
            }
        }

        return mystl::copy(first1, last1, result);
    }

    template <typename InputIter1, typename InputIter2,
            typename OutputIter, typename Compared>
    OutputIter set_difference(nputIter1 first1, InputIter1 last1,
                              InputIter2 first2, InputIter2 last2,
                              OutputIter result, Compared comp) {
        while (first1 != last1 && first2 != last2) {
            if (comp(*first1, *first2)) {
                *result = *first1;
                ++first1;
                ++result;
            }else if (comp(*first2, *first1)) {
                ++first2;
            }else {
                ++first1;
                ++first2;
            }
        }

        return mystl::copy(first1, last1, result);
    }
    /*****************************************************************************************/
    // set_symmetric_difference
    // 计算 (S1-S2)∪(S2-S1) 的结果并保存到 result 中，返回一个迭代器指向输出结果的尾部
    /*****************************************************************************************/
    template <typename InputIter1, typename InputIter2, typename OutputIter>
    OutputIter set_symmetric_difference(nputIter1 first1, InputIter1 last1,
                              InputIter2 first2, InputIter2 last2,
                              OutputIter result) {
        while (first1 != last1 && first2 != last2) {
            if (*first1 < *first2) {
                *result = *first1;
                ++first1;
                ++result;
            }else if (*first2 < *first1) {
                *result = *first2;
                ++first2;
                ++result;
            }else {
                ++first1;
                ++first2;
            }
        }
        return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
    }

    template <typename InputIter1, typename InputIter2, typename OutputIter>
    OutputIter set_symmetric_difference(nputIter1 first1, InputIter1 last1,
                              InputIter2 first2, InputIter2 last2,
                              OutputIter result) {
        while (first1 != last1 && first2 != last2) {
            if (comp(*first1, *first2)) {
                *result = *first1;
                ++first1;
                ++result;
            }else if (comp(*first2, *first1)) {
                *result = *first2;
                ++first2;
                ++result;
            }else {
                ++first1;
                ++first2;
            }
        }
        return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
    }
}  // namespace mystl;
#endif //TINYSTL_SET_ALGO_H
