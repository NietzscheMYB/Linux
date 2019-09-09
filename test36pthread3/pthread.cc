#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#if 0
void* ThreadEntry(void* arg)
{
  (void)arg;
  while(1);
  return NULL;
}

int main()
{ pthread_t tid1;
  pthread_t tid2;
  pthread_t tid3;
  pthread_create(&tid1,NULL,ThreadEntry,NULL);
  pthread_create(&tid2,NULL,ThreadEntry,NULL);
  pthread_create(&tid3,NULL,ThreadEntry,NULL);

  while(1);

  return 0;//top 查看进程列表
}
#endif


#include<sys/time.h>
#define SIZE 10000000

int64_t GetUs()
{
  //秒级int可以，时间戳可能为负，闰秒
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_sec*1000000+tv.tv_usec;//秒与微秒的换算
}

void Calc(int *arr,int beg,int end)
{
  for(int i=beg;i<end;++i)
  {
    arr[i]=arr[i]*arr[i];
  }

}


#if 0
//单线程版本
int main()
{
  int* arr=(int*)malloc(sizeof(int)*SIZE);
  //开始记录时间
  int64_t beg=GetUs();
  Calc(arr,0,SIZE);//包含0，不包括size
  //记录结束时间
  int64_t end=GetUs();
  printf("time->%ld\n",end-beg);
  return 0;
}
#endif



#if 1
//多线程版本
//线程1 Calc(arr,0,size/2)
//线程2 Calc(arr,size/2,size)
#define Thread_num 6

typedef struct Arg{
  int beg;
  int end;
  int* arr;
}Arg;

void* ThreadEntry(void* arg)
{
  Arg* p=(Arg*)arg;
  Calc(p->arr,p->beg,p->end);
  return NULL;
}
int main()
{
  int* arr=(int*)malloc(sizeof(int)* SIZE);
  Arg args[Thread_num];
  int base=0;
  for(int i=0;i<Thread_num;++i)
  {
    args[i].beg=base;
    args[i].end=base+SIZE/Thread_num;
    args[i].arr=arr;
    base+=SIZE/Thread_num;
  }
  pthread_t tid[Thread_num];
  int64_t beg=GetUs();
  for(int i=0;i<Thread_num;i++)
  {
    pthread_create(&tid[i],NULL,ThreadEntry,&args[i]);
  }
  int64_t end=GetUs();
  for(int i=0;i<Thread_num;i++)
  {
    pthread_join(tid[i],NULL);
  }
//  int64_t end=GetUs();
  printf("time=>%ld\n",end-beg);

  return 0;
}
#endif



