#include<iostream>
#include<unistd.h>
#include<pthread.h>
#include<vector>
using namespace std;
//实现一个生产者消费者模型
//首先要有一个交易场所
vector<int> data;//全局
pthread_mutex_t mt;
pthread_cond_t cond;
#if 0
void* Product(void* arg)
{
    (void)arg;
    //负责把数据往交易场所取放
    int count=0;
    while(1)
    {
        pthread_mutex_lock(&mt);
        data.push_back(++count);
        pthread_mutex_unlock(&mt);
        pthread_cond_signal(&cond);
        usleep(789789);
    }
    return NULL;
}

void* Consum(void* arg)
{
    (void)arg;
    //负责把交易场所中的数据取出来
    while(1)
    {
        //每次取最后一个元素
        pthread_mutex_lock(&mt);
        if(data.empty())
        {
            //1.先释放锁
            //2.等待条件就绪（由其他线程调用pthrad_cond_signal）
            //3.如果条件就绪了，重新获取锁
            //1,2必须是原子操作
            //加上了wait之后最大的意义在于如果没有数据，消费者线程
            //不必进行空转，节省了资源
            pthread_cond_wait(&cond,&mt);
        }
        int result=data.back();//如果为空内存访问越界
        data.pop_back();
        printf("result=%d\n",result);
        pthread_mutex_unlock(&mt);
        usleep(123123);
    }
    return NULL;
}

int main()
{
    pthread_cond_init(&cond,NULL);
    pthread_mutex_init(&mt,NULL);
    pthread_t tid1,tid2,tid3,tid4;
    pthread_create(&tid1,NULL,Product,NULL);
    pthread_create(&tid2,NULL,Product,NULL);
    pthread_create(&tid3,NULL,Consum,NULL);
    pthread_create(&tid4,NULL,Consum,NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);
    pthread_join(tid4,NULL);
    pthread_mutex_destroy(&mt);
    pthread_cond_destroy(&cond);
    return 0;
}
#endif

//使用队列来表示生产者消费者模型
//同步互斥不一定非得用互斥锁和条件变量来实现
//使用信号量来完成！！
//信号量计算器！表示可以用资源的个数
//p申请资源，计数器-1
//v释放资源，计数器+1
//当p计数器为0时，再去p操作就会发生阻塞
#if 0
#include<semaphore.h>
#include"BlockingQueue.hpp"

BlockingQueue<int> queue(100);

void* Product(void* arg)
{
    (void)arg;
    int count=0;
    while(1)
    {
        queue.Push(++count);
        usleep(789789);
    }
    return NULL;
}
void* Consume(void* arg)
{

    (void)arg;
    while(1)
    {
        int count=0;
        queue.Pop(&count);
        printf("count=%d\n",count);
        usleep(123123);
    }
    return NULL;
}

int main()
{
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,Product,NULL);
    pthread_create(&tid2,NULL,Consume,NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

    return 0;
}
#endif
#include"BlockingQueue.hpp"
#include"ThreadPool.hpp"

//这个类由用户自定制
//需要依赖哪些数据可用随意修改
class MyTask:public Task
{
public:
    MyTask(int id)
    :id_(id)
    {}
    void Run()//对run函数重写
    {
        //执行用户自定制的逻辑！！
        printf("id=%d\n",id_);
    }
private:
    int id_;
};

int main()
{
    ThreadPool pool(10);
    for(int i=0;i<20;++i)
    {
        pool.AddTask(new MyTask(i));
    }
    while(1)
    {
        sleep(1);
    }
    return 0;
}