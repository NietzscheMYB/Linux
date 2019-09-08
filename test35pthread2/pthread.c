#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<malloc.h>
#if 0 //线程之间共用一份虚拟地址空间
int g_count=0;
void* ThreadEntry(void* arg)
{
  (void)arg;
  int *p=(int*)arg;
  while(1)
  {
    printf("In ThreadEntry,%lu\n",pthread_self());
    ++g_count;
    ++(*p);
    sleep(1);
  }
  return NULL;
}
int main()
{
  int *p=(int*)malloc(4);
  *p=0;
  pthread_t tid;
  int count=0;//栈上变量
  pthread_create(&tid,NULL,ThreadEntry,&count);
  pthread_detach(tid);
  while(1)
  {
    printf("In MainThread,%d\n",count);
    printf("In MainThread,%d\n",g_count);
    sleep(1);
  }
  return 0;
}
#endif

//线程异常终止的情况

void* ThreadEntryd(void* arg)
{
  (void)arg;
  int *p=NULL;
  while(1)
  {
    printf("In ThreadEntry\n");
    *p=10;
    sleep(1);
  }
  return NULL;
}

int main()
{
  pthread_t tid;
  pthread_create(&tid,NULL,ThreadEntryd,NULL);
  while(1)
  {
    printf("In Main Thread\n");
    sleep(1);
  }




  return 0;
}





