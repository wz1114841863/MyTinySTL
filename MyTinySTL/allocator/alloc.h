#ifndef TINYSTL_ALLOC_H
#define TINYSTL_ALLOC_H

// 包含类：alloc, 用于分配和回收内存，以内存池的方式实现
#include <new>
#include <cstddef>
#include <cstdio>

namespace mystl {
    // union: FreeList
    // 采用链表的形式管理内存碎片，分配与回收小内存(<= 4K)区块
    union FreeList {
        char data[1];
        union FreeList *next;
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
        static char* start_free;  // 内存池其实位置
        static char* end_free;    // 内存池结束位置
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

    char*  alloc::start_free = nullptr;
    char*  alloc::end_free = nullptr;
    size_t alloc::heap_size = 0;

    FreeList* alloc::free_list[EFreeListsNumber] = {
            nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,
            nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,
            nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,
            nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,
            nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,
            nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,
            nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr
    };

    // 分配大小为n的空间， n > 0
    inline void *alloc::allocate(size_t n) {
        FreeList *my_free_list;
        FreeList result;
        if (n > static_cast<size_t>(ESmallObjectBytes))
            return std::malloc(n);
        my_free_list = free_list[M_freelist_index(n)];
        result = my_free_list;
        if (result == nullptr) {
            void *r = M_refill(M_round_up(n));
            return r;
        }
        my_free_list = result->next;
        return result;
    }

    // 释放 p 指向的大小为n的空间，p 不能为 0
    inline void alloc::deallocate(void *p, size_t n) {
        if (n > static_cast<size_t>(ESmallObjectBytes)) {
            std::free(p);
            return ;
        }
        FreeList *q = reinterpret_cast<FreeList*>(p);
        FreeList *my_free_list;
        my_free_list = free_list[M_freelist_index(n)];
        q->next = my_free_list;
        my_free_list = q;
    }

    // 重新分配空间，参数一为指向新空间的指针，参数二为原来空间的大小，参数三为申请空间的大小
    inline void *alloc::reallocate(void *p, size_t old_size, size_t new_size) {
        deallocate(p, old_size);
        p = allocate(new_size);
        return p;
    }

    // bytes 对应上调大小
    inline size_t alloc::M_align(size_t bytes) {
        if (bytes <= 512) {
            return bytes <= 256
                ? bytes <= 128 ? EAlign128 : EAlign256
                : EAlign512;
        }
        return bytes <= 2048
            ? bytes <= 1024 ? EAlign1024 : EAlign2048
            : EAlign4096;
    }

    // 讲 bytes 上调至对应区间大小
    inline size_t alloc::M_round_up(size_t bytes) {
        return ((bytes + M_align(bytes) - 1) & ~(M_align(bytes) - 1));
    }

    // 根据区块大小，选择第n个free lists
    inline size_t alloc::M_freelist_index(size_t bytes) {
        if (bytes <= 512) {
            return bytes <= 256
                ? bytes <= 128
                    ? ((bytes + EAlign128 - 1) / EAlign128 - 1)
                    : (15 + (bytes + EAlign256 - 129) / EAlign256)
                : (23 + (bytes + EAlign512 - 257) / EAlign512);
        }
        return bytes <= 2048
            ? bytes <= 1024
                ? (31 + (bytes + EAlign1024 - 513) / EAlign1024)
                : (39 + (bytes + EAlign2048 - 1025) / EAlign2048)
            : (47 + (bytes + EAlign4096 - 2049) / EAlign4096);
    }

    // 重新填充 free list
    void *alloc::M_refill(size_t n) {
        size_t nblock = 10;
        char *c = M_chunk_alloc(n, block);
        FreeList *my_free_list;
        FreeList *result, *cur, *next;
        // 如果只有一个区块，就把这个区块返回给调用者，free list 没有增加新节点
    }
}

#endif //TINYSTL_ALLOC_H
