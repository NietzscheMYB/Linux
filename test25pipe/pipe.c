//从键盘读取数据，写入管道，读取管道，写到屏幕
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
/*
int main(void)
{
  int fds[2];
  char buf[100];
  int len;

  if(pipe(fds)==-1)
  {
    perror("make pipe");
    exit(1);
  }
  //read from stdin
  while(fgets(buf,100,stdin))
  {
   len=strlen(buf);
   //write into pipe
   if(write(fds[1],buf,len)!=len)
   {
      perror("write to pipe");
      break;
   }
   //memset(buf,0x00,sizeof(buf));

   //read from pipe
    if((len=read(fds[0],buf,100))==-1)
    {
      perror("read from pipe");
      break;
    }

    //write to stdout
    if(write(1,buf,len)!=len)
    {
      perror("write to stdout");
      break;
    }
  }
  return 0;
}*/

/*
int main()
{
  //使用pipe函数创建一对文件描述符，通过一对文件描述符
  //就能操作内核的管道
  int fd[2];
  int ret=pipe(fd);
  if(ret<0)
  {
    perror("pipe");
    return 1;
  }

  //fd[0]读数据 fd[1]写数据
  char buf[1024]="hehe";
  write(fd[1],buf,strlen(buf));
  char buf_output[1024]={0};
  ssize_t n=read(fd[0],buf_output,sizeof(buf_output)-1);
  buf_output[n]='\0';

  printf("%s\n",buf_output);
  
  //管道使用完成之后，需要及时关闭文件描述符
  close(fd[0]);
  close(fd[1]);

  return 0;
}
*/

/*
int main()
{
  //使用pipe函数创建一对文件描述符，通过一对文件描述符
  //就能操作内核中的管道
  int fd[2];
  int ret=pipe(fd);//pipe成功时返回0
  if(ret<0)
  {
    perror("pipe");
    return 1;
  }
  //fd[0]读数据 fd[1]写数据
  ret=fork();//以父进程为模板复制，复制pcb，也复制文件描述符
  if(ret>0)
  {
    //father
    //写数据
    char buf[1024]="hehe";
    write(fd[1],buf,strlen(buf));
   // exit(1);
   sleep(30);
  }else if(ret==0)
  {
    //chlid
    //写数据
    printf("%d\n",getpid());
    
    char buf_output[1024]={0};
    int n=read(fd[0],buf_output,sizeof(buf_output)-1);
     buf_output[n]='\0';
    printf("child read %s\n",buf_output);
  }
  close(fd[0]);
  close(fd[1]);


  return 0;
}
*/

int main()
{
  //使用pipe函数创建一对文件描述符，
  //通过文件描述符就能操作内核的管道
  int fd[2];
  int ret=pipe(fd);//成功返回0
  if(ret<0)
  {
    perror("pipe");
    return 1;
  }
  //f[0]读数据  f[1]写数据
  ret=fork();
  if(ret>0)
  {
    //father
    //写数据
    char buf[1024]="hehe";
    write(fd[1],buf,strlen(buf));

    sleep(1);//发生阻塞

    char buf_output[1024]={0};
    int n=read(fd[0],buf_output,sizeof(buf_output)-1);
    buf_output[n]='\0';
    printf("child read %s\n",buf_output);

  }
  else if(ret==0)
  {
    //child 
    //读数据
    char buf_output[1024]={0};
    int m=read(fd[0],buf_output,sizeof(buf_output)-1);
    buf_output[m]='\0';
  }
  //管道使用完成后，需要及时关闭文件描述符
  close(fd[0]);
  close(fd[1]);


  return 0;
}







