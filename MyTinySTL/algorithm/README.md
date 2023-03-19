algorithm 仅用来包含其他算法的头文件  
numeric  数值算法
```
    // accumulate，给定初始值，计算迭代器范围和
    T accumulate(InputIter first, InputIter last, T init);
    
    // adjacent_difference, 计算相邻元素的差值，结果保存到以 result 为起始的区间上
    OutputIter adjacent_difference(InputIter first, InputIter last, OutputIter result);
    
    // inner_product, 给定初始值，计算两个区间的内积
    T inner_product(InputIter1 first1, InputIter1 last1, InputIter1 first2, T init);
    
    // iota, 填充[first, last)，以 value 为初值开始递增
    void itoa(ForwardIter first, ForwardIter last, T value);
    
    // partial_sum 计算局部累计求和，结果保存到以 result 为起始的区间上
    OutputIter partial_sum(InputIter first, InputIter last, OutputIter result);
    
    // pow, 幂指函数
    inline T pow(T x, Interger n)：
```
set_heap 集合算法  
要求有序  
comp 基于 <  
```
    // set_union， S1 ∪ S2
    OutputIter set_union(InputIter1 first1, InputIter1 last1,
                     InputIter2 first2, InputIter2 last2,
                     OutputIter result);
   
    // set_intersection  S1 ∩ S2  
    OutputIter set_intersection(InputIter1 first1, InputIter1 last1,
                     InputIter2 first2, InputIter2 last2,
                     OutputIter result);
   
    // set_difference  S1 - S2   
    OutputIter set_difference(InputIter1 first1, InputIter1 last1,
                            InputIter2 first2, InputIter2 last2,
                            OutputIter result); 
   
    // set_symmetric_difference  (S1-S2)∪(S2-S1)
    OutputIter set_symmetric_difference(InputIter1 first1, InputIter1 last1,
                              InputIter2 first2, InputIter2 last2,
                              OutputIter result);                       
```
heap_algo 与heap相关的算法:  
默认实现大顶堆,由数组存储    
大顶堆可以根据父节点位置获取子节点位置，也可以根据字节点位置获取父节点位置  
大顶堆排序得到的是升序  
```
    // push_heap，新元素已经插入到底部容器的最尾端，调整 heap
    void push_heap(RandomIter first, RandomIter last);
    
    // pop_heap，将 heap 的根节点取出放到容器尾部，调整 heap
    void pop_heap(RandomIter first, RandomIter last);
    
    // sort_heap: 断执行 pop_heap 操作，直到首尾最多相差1
    void sort_heap(RandomIter first, RandomIter last)；
    
    // make_heap, 把容器内的数据变为一个 heap
    void make_heap(RandomIter first, RandomIter last);
    
```
algobase 基础算法：
```
    // max, min, iter_swap 

    // copy: 把 [first, last)区间内的元素拷贝到 [result, result + (last - first))内
    OutputIter copy(InputIter first, InputIter last, OutputIter result);
    
    // copy_backward：将 [first, last)区间内的元素拷贝到 [result - (last - first), result)内
    BidirectionalIter2 copy_backward(BidirectionalIter1 first, BidirectionalIter1 last,
                                     BidirectionalIter2 result);
                                     
    // copy_if, 把[first, last)内满足一元操作 unary_pred 的元素拷贝到以 result 为起始的位置上
    OutputIter copy_if(InputIter first, InputIter last, OutputIter result, UnaryPredicate unary_pred);
    
    // copy_n,把 [first, first + n)区间上的元素拷贝到 [result, result + n)上     
    mystl::pair<InputIter, OutputIter> copy_n(InputIter first, Size n, OutputIter result);
    
    // move, 把 [first, last)区间内的元素移动到 [result, result + (last - first))内  
    OutputIter move(InputIter first, InputIter last, OutputIter result);
    
    // move_backward , 将 [first, last)区间内的元素移动到 [result - (last - first), result)内
    BidirectionalIter2 move_backward(BidirectionalIter1 first, BidirectionalIter1 last,
                                     BidirectionalIter2 result)；
    
    // equal，比较第一序列在 [first, last)区间上的元素值是否和第二序列相等
    bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2)；
    
    // fill_n, 从 first 位置开始填充 n 个值 
    OutputIter fill_n(OutputIter first, Size n, const T &value);
    
    // fill, 为 [first, last)区间内的所有元素填充新值                                                
    void fill(ForwardIter first, ForwardIter last, const T &value);
    
    // mismatch,平行比较两个序列，找到第一处失配的元素，返回一对迭代器，分别指向两个序列中失配的元素
     mismatch(Inputiter1 first1, Inputiter1 last1, Inputiter2 first2);
```