#pragma once

#include<semaphore.h>
#include<unistd.h>
#include<cstdio>
#include<pthread.h>
#include<vector>


//阻塞队列：一种常见的数据结构，线程安全版本的队列
//一般Blockingqueue，都要求长度有上限
//如果队列为空，去执行pop会阻塞
//如果队列满了，去执行push也会阻塞

//信号量表示互斥比较简单，但是表示同步比较复杂

//信号量表示可用资源的个数
//一个信号量表示当前队列中元素的个数
//另一个信号量表示当前队列中空格的个数

//插入元素，消耗空格资源，释放元素资源，
//删除元素就是消耗了一个元素资源，释放了一个空格资源

//如果用信号量表示互斥，p操作和v操作在同一个函数
///如果用信号量表示同步，p操作和v操作在不同的函数中


//信号量这个计算器的+1 -1是原子的
template<typename T>
class BlockingQueue
{
public:
    BlockingQueue(int max_size)
    :max_size_(max_size)
    ,head_(0)
    ,tail_(0)
    ,size_(0)
    ,queue_(max_size)
    {
        sem_init(&lock_,0,1);//可用资源为1个 第二个参数为0 ，表示只在当前进程中，
        sem_init(&elem_,0,0);
        sem_init(&blank_,0,max_size);
    }
    ~BlockingQueue()
    {
        sem_destroy(&lock_);
        sem_destroy(&elem_);
        sem_destroy(&blank_);
    }
    void Push(const T& data)
    {
        //每次要插入元素，就得先申请一个空格资源
        //如果没有空格资源 （信号量为0），说明队列满了；
        //满了就不能在继续插入，并且在push中阻塞
        sem_wait(&blank_);//申请一个空格资源！！！！！！


        sem_wait(&lock_);
        queue_[tail_]=data;
        ++tail_;
        ++size_;
        sem_post(&lock_);

        sem_post(&elem_);//
    }
    //data表示出队列的这个元素
    void Pop(T* data)  //输出型参数
    {
        //每次出队列 先申请一个元素资源
        //如果没有元素资源，队列为空
        //就不能直接出队列，而需要在pop处位置阻塞
        sem_wait(&elem_);

        sem_wait(&lock_);
        *data=queue_[head_];
        ++head_;
        --size_;
        sem_post(&lock_);

        sem_post(&blank_);///释放空格
    }
private:
    std::vector<T> queue_;
    int head_;
    int tail_;
    int size_;
    int max_size_;
    sem_t lock_;//可以用二元信号量表示互斥锁  （非0即1）表示互斥锁
    sem_t elem_;//可用元素个数
    sem_t blank_;//可用空格个数
};