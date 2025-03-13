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
## \<thread>\标准库
多线程共享相同的地址空间。thread在构造完成后，就已经开始执行线程。
  - 函数：
    1. join：join函数会阻塞当前调用的函数，并等待线程执行完毕后的返回结果。（保证同步的机制）
    2. detach：让子线程独立执行，主线程不必等待
    3. get_id：返回当前线程的唯一标识符
    4. hardware_concurrency：返回硬件核心数，支持的线程并行数量
## \<future>\标准库
- promise：promise对象存储某种类型的值，这个值可以被future对象取回（可以在其他线程中），这个promise本身提供了一个同步点。promise对象关联了一个shared status，通过调用get_future可以将shared status关联到一个future对象。
  - 调用get_future后，promise对象和future对象可以共享相同的shared status
    1. primise：异步provider，给shared status设置值的
    2. future：异步返回对象，从shared status中取值的
  - 函数：
    1. set_value：给promise包裹的类型赋值
    2. get_future：返回与shared status相关的future对象
- future：可以从provider或者function中取回值，在不同的线程中正确的同步访问。
  - 函数：
    1. get：等待获取promise中包裹类型对应的值
