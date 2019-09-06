#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<wait.h>
/*void MyHandler(int signo)
{
  printf("signo=%d\n",signo);
}
int main()
{
  signal(2,MyHandler);//捕获信号
  signal(3,MyHandler);
  while(1)
  {
    sleep(1);
  }
  return 0;
}*/

void MyHandler(int sig)
{
  (void)sig;
  printf("child exit\n");
  while(1)
  {
    //如果ret>0 已经回收到一个子进程的，返回子进程的pid
    //如果ret==0 还有子进程在，但是子进程没结束
    //ret<0 没有子进程了
    int ret=waitpid(-1,NULL,WNOHANG);
    if(ret>0)
    {
      //继续循环
    }else{
      //退出循环
      break;
    }
  }
}


int main()
{
  signal(SIGCHLD,MyHandler);
  int i=0;
  for( i=0;i<20;i++)
  {
    pid_t ret=fork();
    if(ret==0)
    {
      printf("child pid %d\n",getpid());
    }
  }
  while(1)
  {
    sleep(1);
  }
  return 0;
}
