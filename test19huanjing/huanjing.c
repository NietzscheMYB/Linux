/*env也是一个字符串数组
 * env数组也有一个结束标记NULL
 * 当前环境变量都有啥
 * main函数三种形式
 * 1.没参数
 * 2.int argc,char* argv[]
 * 3.int argc,cahr* argv[],char* env[]*/
//#include<iostream>
//#include<cstdio>
#include<stdio.h>
#include<unistd.h>

/*int main(int argc,char *argv[],char* env[])
{
    (void)argc;
      (void)argv;
        (void)env;

        printf("argc:%d\n",argc); 
        for(int i=0;i<argc;i++)
            {
                 printf("%s\n",argv[i]);
                    
            }
              for(int j=0;env[j]!=NULL;++j)
              {
  
                   printf("%s\n",env[j]);

                      
              }
                
  return 0;
}*/
/*env也是一个字符串数组
 * env数组也有一个结束标记NULL
 * 当前环境变量都有啥
 * main函数三种形式
 * 1.没参数
 * 2.int argc,char* argv[]
 * 3.int argc,cahr* argv[],char* env[]*/
int main(int argc, char *argv[], char *env[]) {    int i = 0;    for(; env[i]; i++){        printf("%s\n", env[i]);     }    return 0;  }
