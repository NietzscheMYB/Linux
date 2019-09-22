#include<stdio.h>
#include<iostream>
#include<unistd.h>
#include<pthread.h>
#include<vector>
using namespace std;

//生产者消费者模型3,2,1
//3个关系，生产生产互斥，消费消费互斥，生产消费同步互斥
//2给角色 生产者 消费者
//1.个交易场所

//交易场所
vector<int> data;

//加锁
pthread_mutex_t mt;


//加锁只是让消费者与消费者保持互斥，生产者与生产者保持互斥，没有让消费者与生产者保持互斥与同步
//要让生产者与消费者存在同步与互斥
pthread_cond_t cd;

void* Product(void* arg)
{
    (void)arg;
    //负责把数据往交易场所里放
    int count=0;
    while(1)
    {
        //线程与线程之间共享的是虚拟地址空间，与文件描述符表！！！
        //全局变量
        //不共享的是erro错误码，栈空间（栈上的变量局部变量）  上下文信息！！！
        pthread_mutex_lock(&mt);
        data.push_back(++count);
        pthread_mutex_unlock(&mt);
        pthread_cond_signal(&cd);
        usleep(789789);
    }
    return NULL;
}

void* Consume(void* arg)
{
    (void)arg;

    
    //从交易场所中读数据
    while(1)
    {
        pthread_mutex_lock(&mt);
        while(data.empty())  //   写成while
        {
            //pthread_cond_wait 做三件事情
            //1.先释放锁
            //2.等待条件就绪（有其他线程调用pthread_cond_signal）
            //3.如果条件就绪，就重新获取锁
            //1，2操作必须是原子的操作
            //加上wait之后，最大的意义在于如果没有数据，消费者线程
            //不必进行空转，节省了资源！！。

            //没有数据，就会在这等待！！
           pthread_cond_wait(&cd,&mt);
        }
        //如果为空内存访问越界
        //所有加上判空条件
        int result=data.back();
        data.pop_back();
        printf("result=%d\n",result);
        pthread_mutex_unlock(&mt);
        //usleep(123123);
    }

    

    #if 0 
      while(1)
    {
        //每次取最后一个元素
        pthread_mutex_lock(&mt);
        if(!data.empty())
        {
            int result=data.back();//如果为空内存访问越界
            data.pop_back();
            printf("result=%d\n",result);
        }
        pthread_mutex_unlock(&mt);
       // usleep(123123);
    }
    #endif
    return NULL;
}

int main()
{
    pthread_cond_init(&cd,NULL);
    //第二个参数，设置锁的属性！！！先设置为NULL
    pthread_mutex_init(&mt,NULL);
    pthread_t tid1,tid2,tid3,tid4,tid5;
    //第二个参数设置线程属性！！！
    //第四个参数设置线程入口函数参数！！！
    pthread_create(&tid1,NULL,Product,NULL);
    pthread_create(&tid2,NULL,Consume,NULL);
    pthread_create(&tid3,NULL,Product,NULL);
    pthread_create(&tid4,NULL,Consume,NULL);
    pthread_create(&tid5,NULL,Consume,NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);
    pthread_join(tid4,NULL);
    pthread_join(tid5,NULL);

    pthread_mutex_destroy(&mt);
    pthread_cond_destroy(&cd);
    return 0;
}