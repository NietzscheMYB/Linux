#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int main()
{
  int fd=open("myfifo",O_WRONLY);//open 返回值是文件描述符  fopen返回值是file*
  if(fd<0)
  {
    perror("open");//标准错误 输出到屏幕
  }
  while(1)
  {
    printf("->");
    fflush(stdout);
    char buf[1024]={0};
   // gets(buf);
  ssize_t n=read(0,buf,sizeof(buf)-1);//从标准输入中读数据
    buf[n]='\0';
    write(fd,buf,strlen(buf));

  }
  return 0;
}





