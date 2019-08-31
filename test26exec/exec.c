//进程程序替换
//fork创建的子进程，和父进程是共有一份代码，而事实上
//我们需要的是创建出子进程能够执行一份单独的代码

//子进程往往要调用一种exec函数来执行另一个程序。当进程调用
//一种exec函数时，该进程的用户空间代码和数据完全被新程序替换，
//从新程序的启动例程开始执行

//调用exec并不是创建新进程，所以调用exec前后该进程的id并未改变


//1.程序替换并不会创建新进程，也不会销毁进程
//2.替换代码和数据(从一个可执行文件中来)
//3.原有的堆和栈的数据全部不要，根据新的代码执行过程，从新构建堆和栈
//


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
/*
int main()
{
  printf("before execl\n");

  //最后一个参数必须是null ，如果不填程序就是未定义
  int ret=execl("/usr/bin/ls","ls","-l","/",NULL);
  printf("after execl %d",ret);//替换成功就不会执行这条语句了
 //不管后面是啥 ，都没有了
 //所以 先fork()复制一份代码，然后子进程替换
  return 0;
}*/

int main()
{
  pid_t ret=fork();
  if(ret==0)
  {
    //child
    //---------------------
    //最后一个参数必须是null，如果不填就是未定义
   // printf("before execl\n");
   // execl("/usr/bin/ls","ls","/",NULL);
    

    //---------------
   // printf("before execlp\n");//p完整的路径
   // execlp("ls","ls","-l","/",NULL);//最后一个参数必须是null,如果不填就是未定义
    

    char* env[]={"AAA=BBB",NULL};//这数组必须以null结尾
    printf("before execl\n");
    execle("./aaa","./aaa",NULL,env);


  }
  else{
    //father
    wait(NULL);//等待子进程结束
   // printf("after execl\n");
   // 
   printf("after execlp");
  }
  return 0;
}











