#include<unistd.h>
#include<pthread.h>
#include<stdio.h>

void* ThreadEntry(void* arg)
{
  (void)arg;
  while(1)
  {
    printf("In ThreadEntry,%lu\n",pthread_self());
    sleep(1);
  }

}

int main()
{
  pthread_t id;
  pthread_create(&id,NULL,ThreadEntry,NULL);//第一个参数id号，第二个线程属性，默认NULL，第三个线程入口函数，第四个线程入口函数的参数
  while(1)
  {
    printf("In Main pthread,%lu\n",pthread_self());
    
    sleep(1);
  }

  return 0;
}
