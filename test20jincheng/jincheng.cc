#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<unistd.h>
#include<sys/wait.h>
using namespace std;
int main()
{
 /* for(size_t i=0;i<2;i++)
  {
    fork();
    printf("=");
  }
  sleep(1);
  return 1;
*/
 /* exit(1);
  printf("hehe\n");
 */
  pid_t ret=fork();
  if(ret>0)
  {
    //father
    cout<<"father:"<<getpid()<<endl;
    int status=0;
    //阻塞式函数！！
    pid_t result=wait(&status);//输出型参数
    cout<<"result"<<result<<" "<<"status:"<<status<<endl;
   if(status&0xff)//看status最低一个字节看进程是否异常
   {
     //异常终止
     cout<<"异常终止，信号为："<<(status&0x7f)<<endl;
   }
   else{
     //正常终止
     cout<<"正常终止，退出码为："<<(status>>8)<<endl;
   }
  }else if (ret==0)
  {
    int count=1000;
    while(count>0)
    {
      printf("child %d\n",getpid());
      sleep(1);
      --count;
    }
    exit(0);
  }
  else{
    perror("fork");
  }
  return -0;
}
