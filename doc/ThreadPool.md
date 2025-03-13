# 线程池
> 程序中，如果需要多次使用线程，就意味着多次创建并销毁线程。
> 创建和销毁线程的过程势必会消耗内存，线程过多会带来调动的开销，影响缓存局部性和整体性能

## 线程池的构成
- 线程池管理器：用于创建并管理线程池，允许动态调整线程池的线程数，处理线程池声明周期
- 任务队列：保存待执行的任务，任务队列需要保证线程安全，支持多个线程同时访问
- 任务调度：每个线程从任务队列中取出任务，执行任务后再等待新的任务

## 使用的标准库
- thread
- mutex
- condition_variable
- queue


## \<atomic\>标准库
- atomic类型
  包裹了一种类型，可以保证不会造成数据竞争，可以用于在不同线程之间同步内存访问
- atomic_flag类型
  - boolean atomic类型，所有库实现中唯一保证了无锁并发（lock-free）的类型，可以设置为ATOMIC_FLAG_INIT
  - 函数：
    1. test_and_set: 将flag置位
    2. clear：将flag清除
- load()函数
  - 返回atomic对象包含的类型所对应的值，该函数可以遵循指定的内存序
  - 内存序：
    1. memory_order_relaxed
    2. memory_order_consume
    3. memory_order_acquire
    4. memory_order_release
    5. memory_order_acq_rel
    6. memory_order_seq_cst: 顺序一致性
## shared_ptr | unique_ptr
- 直接使用构造函数创建只能指针和make_shared有什么不同？
  ```C++
  // 直接使用
  std::shared_ptr<int> p(new int(100));

  // 使用make_shared
  auto p = std::make_shared<int>(100);
  ```
  直接使用构造函数会进行两次内存分配，一个是原始对象的内存分配，另一个是内部计数器的内存分配，而使用make_shared只需要一次内存分配
## \<condition_variable>\标准库
- condition_variable：能够阻塞调用的线程，直到被通知重新开始。调用wait函数之前，使用unique_lock去锁定线程。线程会保持阻塞状态，直到其他线程在同一个condition_variable调用notification函数。（使用condition_variable之前一定要先用一下unique_lock）
- 函数：
  1. wait
  2. wait_for
