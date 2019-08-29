#include<iostream>
#include<unistd.h>
#include<cstdio>
#include<cstdlib>


int main()
{
  char *const argv[]={"ps","-ef",NULL};
  char *const envp[]={"PATH=/bin:/usr/bin","TERM=console",NULL};
  
  execl("/bin/ps","ps","-ef",NULL);

  //带p的，可以使用环境变量PATH，无需写全路径
  execlp("ps","ps","-ef",NULL);

  //带e的，需要自己组装环境变量
  execle("ps","ps","-ef",NULL,envp);

  execv("/bin/ps",argv);

  //带p的，可以使用环境变量PATH，无需全写路径
  execvp("ps",argv);

  //带e的，需要自己组装环境变量
  execve("/bin/ps",argv,envp);
  exit(0);
  
  return 0;
}
