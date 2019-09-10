#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<signal.h>
pthread_mutex_t mutex;
#define Thread_num 2
int g_count=0;

#if 0
int g_count=0;
void* ThreadEntry(void* arg)
{
  (void)arg;
  for(int i=0;i<50000;i++)
  {
    //如果当前锁已经被其他线程获取到了，当前线程在想
    //获取，就会在lock函数阻塞
    pthread_mutex_lock(&mutex);
    ++g_count;
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}
int main()
{
  pthread_mutex_init(&mutex,NULL);
  pthread_t tid[Thread_num];
  for(int i=0;i<Thread_num;i++)
  {
    pthread_create(&tid[i],NULL,ThreadEntry,NULL);
  }
  for(int i=0;i<Thread_num;i++)
  {
    pthread_join(tid[i],NULL);
  }
  printf("%d\n",g_count);
  pthread_mutex_destroy(&mutex);
  return 0;
}
#endif

#if 0

void ModifyCount()
{
  pthread_mutex_lock(&mutex);
  ++g_count;
  printf("befor sleep\n");
  sleep(1);
  printf("after sleep\n");
  pthread_mutex_unlock(&mutex);
}


void* ThreadEntry(void* arg)
{
  (void)arg;
  for(int i=0;i<50000;i++)
  {
    ModifyCount();
  }
  return NULL;
}

void MyHandler(int sig)
{
  (void)sig;
  ModifyCount();
}
int main()
{
  //SIGNIT 2号信号，ctlr+c产生
  signal(2,MyHandler);
  pthread_mutex_init(&mutex,NULL);
  pthread_t tid[Thread_num];
  for(int i=0;i<Thread_num;i++)
  {
    pthread_create(&tid[i],NULL,ThreadEntry,NULL);
  }
  for(int i=0;i<Thread_num;i++)
  {
    pthread_join(tid[i],NULL);
  }
  printf("%d\n",g_count);
  pthread_mutex_destroy(&mutex);
  return 0;
}
#endif

pthread_cond_t cond;//条件变量

void* ThreadEntry1(void* arg)
{
  (void)arg;
  while(1)
  {
    printf("传球\n");
    pthread_cond_signal(&cond);//等待通知
    usleep(789789);
  }
  return NULL;
}

void* ThreadEntry2(void* arg)
{
  (void)arg;
  while(1)
  {
    printf("扣篮\n");
    //搭配互斥锁使用
    //执行这个pthread_cond_wait 函数就导致线程阻塞
    //阻塞到什么时候？等待其他线程发送一个通知
    pthread_cond_wait(&cond,&mutex);
    printf("扣篮\n");
    usleep(123456);
  }
  return NULL;
}

int main()
{
  pthread_mutex_init(&mutex,NULL);
  pthread_cond_init(&cond,NULL);
  pthread_t tid1,tid2;
  pthread_create(&tid1,NULL,ThreadEntry1,NULL);
  pthread_create(&tid2,NULL,ThreadEntry2,NULL);

  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);


  return 0;
}








