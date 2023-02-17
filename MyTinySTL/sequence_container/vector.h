#ifndef TINYSTL_VECTOR_H
#define TINYSTL_VECTOR_H

// vector 头文件

// 异常保证
// mystl::vecotr<T> 满足基本异常保证，部分函数无异常保证，并对以下函数做强异常安全保证：
//   * emplace
//   * emplace_back
//   * push_back
// 当 std::is_nothrow_move_assignable<T>::value == true 时，以下函数也满足强异常保证：
//   * reserve
//   * resize
//   * insert

#include <initializer_list>
#include "../iterator/iterator.h"
#include "../utils/util.h"
// 还有一部分文件未完成

namespace mystl {

#ifdef max
#pragma message("#undefing marco max")
#undef max
#endif // max

#ifdef min
#pragma message("#undefing marco min")
#undef min
#endif // min
#pagma

    // vector
    template <typename T>
    class vector {
        static_assert(!std::is_same<bool, T>::value, "vector<bool> is not support in mystl.");
    public:
        // 嵌套类型定义
        typedef mystl::allocator<T>                         allocator_type;
        typedef mystl::allocator<T>                         data_allocator;

        typedef typename allocator_type::value_type         value_type;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::size_type          size_type;
        typedef typename allocator_type::difference_type    difference_type;

        typedef value_type*                                 iterator;
        typedef const value_type*                           const_iterator;
        typedef mystl::reverse_iterator<iterator>           reverse_iterator;
        typedef mystl::reverse_iterator<const_iterator>     const_reverse_iterator;

        allocator_type get_allocator() { return data_allocator(); }

    private:
        iterator begin_;  // 记录目前使用空间的头部
        iterator end_;  // 记录目前使用空间的尾部
        iterator cap_;  // 表示目前储存空间的尾部

    public:
        // 构造, 复制, 移动, 析构
        vector() noexcept {
            try_init();
        }

        explicit vector(size_type n) {
            fill_init(n, value_type());
        }

        vector(size_type n, const value_type& value) {
            fill_init(n, value);
        }

        template<typename Iter, typename std::enable_if<
                mystl::is_input_iterator<Iter>::value, int>::type = 0>
        vector<Iter first, Iter last> {
            MYSTL_DEBUG(!(last < first));
            range_init(first, last);
        };

        vector(const vector &rhs) {
            range_init(rhs.begin_, rhs.end_);
        }

        vector(vector &&rhs) noexcept
        :begin_(rhs.begin_), end_(rhs.end_), cap_(rhs.cap_) {
            rhs.begin_ = nullptr;
            rhs.end_ = nullptr;
            rhs.cap_ = nullptr;
        }

        vector(std::initializer_list<value_type> ilist) {
            range_init(ilist.begin(), ilist.end());
        }

        vector& operator=(const vector &rhs);
        vector& operator=(vector &&rhs) noexcept;

        vector& operator=(std::initializer_list<value_type> ilist) {
            vector tmp(ilist.begin(), ilist.end());
            swap(tmp);
            return *this;
        }

        ~vector() {
            destroy_and_recover(begin_, end_, cap_ - begin_);
            begin_ = end_ = cap_ = nullptr;
        }

    public:
        // 迭代器
        iterator begin() noexcept {
            return begin_;
        }

        const_iterator begin() const noexcept {
            return begin_;
        }

        iterator end() noexcept {
            return end_;
        }

        const_iterator end() const noexcept {
            return end_;
        }

        reverse_iterator rbegin() noexcept {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const noexcept {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend() noexcept {
            return reverse_iterator(begin());
        }

        const reverse_iterator rend() const noexcept {
            return reverse_iterator(begin());
        }

        const_iterator cbegin() const noexcept {
            return begin();
        }

        const_iterator cend() const noexcept {
            return end();
        }

        const_reverse_iterator crbegin() const noexcept {
            return rbegin();
        }

        const_reverse_iterator crend() const noexcept {
            return rend();
        }

        // 容量查询
        bool empty() const noexcept {
            return begin_ == end_;
        }

        size_type size() const noexcept {
            return static_cast<size_type>(end_ - begin_);
        }

        size_type max_size() const noexcept {
            return static_cast<size_type>(-1) / sizeof(T);
        }

        size_type capacity() const noexcept {
            return static_cast<size_type>(cap_ - begin_);
        }

        // 访问元素
        reference operator[](size_type n) {
            MYSTL_DEBUG(n < size());
        }
    };
}
#endif //TINYSTL_VECTOR_H
