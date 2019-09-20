#pragma once

#include<vector>
#include<pthread.h>
#include<semaphore.h>
using namespace std;

//一般blokingqueue 都要求长度有上限
//如果队列为空，去pop 就会阻塞
//如果队列满了，去执行push也会阻塞
//信号量表示互斥简单，同步比较难

//信号量表示可用资源的个数
//一个信号量表示当前队列中元素的个数
//另一个信号量表示当前队列中空格的个数
//插入元素就是消耗一个空格资源，释放一个元素资源
//删除元素就是消耗了一个元素资源，释放了一个空格资源
//如果用信号量表示互斥，p操作和v操作在同一个函数中
//如果用信号量表示同步，p操作和v操作在不同的函数中
template<typename T>
class BlockingQueue    //环形队列
{
public:
    BlockingQueue(int max_size)
        :max_size_(max_size)
        ,head_(0)
        ,tail_(0)
        ,size_(0)
        ,queue_(max_size)//vector 元素个数设为max_size
    {
        sem_init(&lock_,0,1);
        sem_init(&elem_,0,0);
        sem_init(&blank_,0,max_size);
    }
    ~BlockingQueue()
    {
        sem_destroy(&lock_);
        sem_destroy(&elem_);
        sem_destroy(&blank_);
    }
    //入队列
    void Push(const T& data)
    {
        //每次要插入元素，就得先申请一个空格资源
        //如果没有空格资源(信号量为0)，说明队列满了
        //满了就不能继续插入元素，并且在Push中阻塞
        sem_wait(&blank_);
        sem_wait(&lock_);
        queue_[tail_]=data;
        ++tail_;
        ++size_;
        sem_post(&lock_);
        sem_post(&elem_);
    }
    //出队列
    void Pop(T* data)
    {
        //每次出队列的时候，就先释放一个元素资源
        //如果没有元素资源，队列为空
        //就不能直接出队列，而需要在Pop的位置阻塞
        sem_wait(&elem_);
        sem_wait(&lock_);
        *data=queue_[head_];
        ++head_;
        --size_;
        sem_post(&lock_);
        sem_post(&blank_);
    }
private:
    vector<T> queue_;
    int head_;
    int tail_;
    int size_;
    int max_size_;//当size_等于max_size_ 时，队列满了
    sem_t lock_;//借助信号量，表示互斥锁，借用一个二元信号量(非0即1))
    sem_t elem_;//可用元素的个数
    sem_t blank_;//可用空格的个数
};