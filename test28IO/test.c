#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
/*int main()
{
  //重定向 依赖操作系统的底层行为
  close(1);
  int fd=open("xx.txt",O_WRONLY|O_CREAT); //返回文件描述符
 // fprintf(stderr,"fdiiiii=%d\n",fd);
  printf("%d\n",stderr->_fileno);
  printf("新的输出：%d\n",stdout->_fileno) ;
  fprintf(stdout,"新的输出：%d\n",stdout->_fileno);
 
  return 0;
}*/

int main()
{
  close(1);
  int fd=open("xx.txt",O_WRONLY);
  printf("hehe\n");
  fprintf(stdout,"haha\n");
  write(1,"miaomiao\n",strlen("maiomiao\n"));//stdout 是file*
  fork();
  return 0;
}
