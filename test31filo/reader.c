#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{
  //mkfifo  xxx  创建命名管道
  //出先 p类型的文件，为管道文件
   
  // 对命名管道的操作和文件的操作是一模一样的
 int fd= open("myfifo",O_RDONLY);
  if(fd<0)
  {
    perror("open");
    return 1;
  }
  while(1)
  {
    char buf[1024]={0};
    ssize_t n=read(fd,buf,sizeof(buf)-1);//没有读到阻塞
    if(n==0)
    {
      //所有写端关闭，读端已经读完
      printf("read done\n");
      return 0;
    }
    buf[n]='\0';
    printf("read %s\n",buf);
  }
  return 0;
}
