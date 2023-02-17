#ifndef TINYSTL_ALLOC_H
#define TINYSTL_ALLOC_H

// 包含类：alloc, 用于分配和回收内存，以内存池的方式实现
#include <new>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>

namespace mystl {
    // union: FreeList
    // 采用链表的形式管理内存碎片，分配与回收小内存区块
    union FreeList {
        union FreeList *next;
        char data[1];
    };

    // 不同内存范围的上调大小
    enum {
        EAlign128 = 8,
        EAlign256 = 16,
        EAlign512 = 32,
        EAlign1024 = 64,
        EAlign2048 = 128,
        EAlign4096 = 256
    };

    // 小对象的内存大小
    enum {ESmallObjectBytes = 4096};
    // free lists 个数
    enum {EFreeListsNumber = 56};

    // 空间配置类：alloc
    // 如果内存过大，超过4096 bytes, 直接调用 std::malloc, std::free
    // 当内存较小时，以内存池管理，每次配置一大块内存，并维护对应的自由链表
    class alloc {
    private:
        static char *start_free;  // 内存池起始位置
        static char *end_free;    // 内存池结束位置
        static size_t heap_size;  // 申请heap空间附加值大小

        static FreeList *free_list[EFreeListsNumber];  // 自由链表

    public:
        static void *allocate(size_t n);
        static void deallocate(void *p, size_t n);
        static void *reallocate(void *p, size_t old_size, size_t new_size);

    private:
        static size_t M_align(size_t bytes);
        static size_t M_round_up(size_t bytes);
        static size_t M_freelist_index(size_t bytes);
        static void *M_refill(size_t n);
        static char *M_chunk_alloc(size_t size, size_t &nobj);
    };


}  // namespace mystl
#endif //TINYSTL_ALLOC_H
