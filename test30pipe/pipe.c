#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>
/*int main()
{
  pid_t ret=fork();
  if(ret==0)
  {
    wait(NULL);//该进程没有子进程 写这个没有什么用
    printf("child %d\n",getpid());
   // wait(NULL);
  }
  else{
    
    printf("father %d\n",getpid());
  }
}
*/


/*
int main()
{
  int fd[2];
  int ret=pipe(fd);
  if(ret<0)
  {
    perror("ret");//标准错误  打印到显示器上
  }
  //fd[0] 读数据        fd[1]写数据
  ret=fork();
  if(ret==0)
  {
    //child;
    char buf_output[1024]={0};

    //当管道中没有数据时
    //发生read阻塞
    int n=read(fd[0],buf_output,sizeof(buf_output)-1);
    buf_output[n]='\0';
    printf("child %s",buf_output);
  }
  else{
    //father
   // sleep(10);
 //  wait(NULL);
    char buf[1024]="hehe";
    write(fd[1],buf,strlen(buf));
    
  }

  close(fd[0]);//及时关闭文件描述符
  close(fd[1]);

  return 0;
}*/


/*
int main()
{
  int fd[2];
  int ret=pipe(fd);
  if(ret<0)
  {
    perror("pipe");
  }
  int count=0;
  while(1)
  {
    //write(fd[1],'a',1);
    char buf[1024]="a";
    ssize_t x=write(fd[1],buf,1);
    count++;
    printf("count %d\n",count);
  }
  return 0;
}*/


int main()
{
  int fd[2];
  int ret=pipe(fd);
  ret=fork();
  if(ret>0)
  {
    //father
    char buf[1024]="hehe";
    write(fd[1],buf,strlen(buf));
    sleep(1);
    char out_f[1024]={0};
    int n=read(fd[0],out_f,sizeof(out_f)-1);
    out_f[n]='\0';
    printf("father  %d   %s\n",getpid(),out_f);
  }else{
    printf("child %d\n",getpid());
    char out_c[1024]={0};
    int n=read(fd[0],out_c,sizeof(out_c)-1);
    out_c[n]='\0';
    printf("child   %d    %s\n",getpid(),out_c);
  }



  return 0;
}

/*
int main()
{
 // printf("hehe\n");
 
  pid_t pid=fork();
  if(pid==0)

  {
    printf("child %d",getpid());
   // while(1);
  }
  else{
    wait(NULL);
    while(1){

    }
    printf("father %d",getpid());
  }
  return 0;
}*/


