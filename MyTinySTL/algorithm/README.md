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