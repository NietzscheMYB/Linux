#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
//intput 表示待切分命令
//output 表示切分结果(字符串数组)
//返回值表示output中包含了几个有效元素
int Split(char intput[],char* output[])
{
  char* p=strtok(intput," ");
  int i=0;
  while(p!=NULL)
  {
    output[i]=p;
    ++i;
    p=strtok(NULL," ");
  }
  output[i]=NULL;//这个操作很容易被忘记
  return i;
}

void CreateProcess(char* argv[],int n)
{
  (void) n;
  //1.创建子进程
  pid_t ret=fork();
  //2.父进程进行进程等待，子进程进行程序替换
  if(ret>0)
  {
    //father
    //暂时先这么写，正常的话一个shell
    //是应该知道子进程的退出码
    wait(NULL);
  }
  else if(ret==0)
  {
    //child
    ret=execvp(argv[0],argv);
    //if条件可以省略，如果exec成功了
    //是肯定不会执行到这个代码的
    perror("exec");
    exit(0);
  }
  else{
    perror("fork()");
  }
}


int main()
{
  while(1)
  {//1.打印提示符
    printf("[---@localhost]$ ");
    fflush(stdout);
    //2.用户输入一个指令
    char command[1024]={0};
    gets(command);//一次读一行数据
    //3.解析指令，把要执行那个程序识别出来
    //那些是命令行参数识别出来 (字符串切分)
    //切分结果应该是一个字符串数组
    char* argv[1024];
    int n=Split(command,argv);
    CreateProcess(argv,n);
  }
  return 0;
}
