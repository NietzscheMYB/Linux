#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>
#include<sys/ipc.h>
/*int CreateShm()
{
  key_t key=ftok(".",0x1);
  if(key==-1)
  {
    perror("ftok");
    return 1;
  }
printf("key=%d\n",key);
  //创建共享内存
  
  int ret=shmget(key,IPC_CREAT|IPC_EXCL|0666);
  //0666 为共享内存的权限
  
  if(ret<0)
  {
    perror("shmget");
    return 1;
  }
  printf("共享内存标识rer=%d\n",ret);
  return ret;
}

int main()
{
  //往共享内存中写数据
  int shmid=CreateShm();
  //2.附件到共享内存对象上
  char *p=(char*)shmat(shmid,NULL,0);
  //3.直接使用
  strcpy(p,"hehe\n");
  


  return 0;
}*/


int main()
{
  //创建共享内存
  key_t key=ftok(".",0x1);
  int shid=shmget(key,32,IPC_CREAT|0664);
  if(shid<0)
  {
    perror("shmgetg");
    return -1;
  }
  //映射连接
  char* shm_start=shmat(shid,NULL,0);
  if(shm_start==(void*)-1)
  {
    perror("shmat error");
    return -1;
  }
  int i=0;
  while(1)
  {
    printf("%s",shm_start);
    sleep(1);
  }
  //解除映射
  shmdt(shm_start);
  shmctl(shid,IPC_RMID,NULL);



  return 0;
}

