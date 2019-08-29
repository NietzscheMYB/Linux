#include<iostream>
#include<cstdlib>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<errno.h>
#include<cstdio>

using namespace std;
/*int main(void)
{
  pid_t pid=fork();
  if(pid==-1)
  {
    perror("fork()");
  }else if(pid==0)
  {
    //child
    cout<<getpid()<<endl;
    sleep(10);

    exit(10);
  }else
  {
    //father
    int st;
    int ret=wait(&st);
    if(ret>0&&(st&0x7f)==0)
    {
      //正常终止，低7位为0
      cout<<"child exit code:"<<((st>>8)&0xff)<<endl;
    }
    else{
      //异常退出
      cout<<"sig code: "<<(st&0x7f)<<endl;
    }

   }
}
*/



//进程阻塞等待方式
/*int main()
{
  pid_t pid=fork();
  if(pid<0)
  {
    perror("fork()");

  }
  else if(pid==0)
  {
    //child
    cout<<"child is running ,pid is "<<getpid()<<endl;
    sleep(5);
    exit(257);
  }else{
    int status=0;
    pid_t ret=waitpid(-1,&status,0);//阻塞式等待，等待5s
    cout<<"waitting~"<<endl;
    if(WIFEXITED(status)&&ret==pid)
    {
      cout<<"wait child 5s success,return code:"<<WEXITSTATUS(status)<<endl;

    }else{
      cout<<"等待失败"<<endl;
    }
  }
  return 0;
}*/

//进程的非阻塞等待
int main()
{
  pid_t pid=fork();
  if(pid<0)
  {
    perror("fork()");
  }
  else if(pid==0)
  {
    //child
    cout<<"childe is running,pid is "<<getpid()<<endl;
    sleep(5);
    exit(1);
  }else{
    //father
    int status=0;
    pid_t ret=0;
    do{
      ret=waitpid(-1,&status,WNOHANG);//非阻塞式等待
      if(ret==0)
      {
        cout<<"childe is running"<<endl;
      }
      sleep(1);
    }while(ret==0);
    if(WIFEXITED(status)&&ret==pid)
    {
      cout<<"等待成功，child pid ："<<WEXITSTATUS(status)<<endl;

    }
    else{
      cout<<"等待失败！"<<endl;
    }
  }
  return 0;
}













