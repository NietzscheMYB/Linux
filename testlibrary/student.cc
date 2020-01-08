#include"show.hpp"
#include"student.hpp"

int main()
{
  MYSQL* connect_fd=MySQLInit();
  StudentTable st(connect_fd);
  BookTable bt(connect_fd);
  while(1)
  {
     menu();
    int flag=0;
    cin>>flag;
    switch (flag)
    {
      case 1:table1();table1fun(st,bt);break;
      case 2:cout<<"bye"<<endl;return 0;
      default:cout<<"输入错误，请重新输入"<<endl;break;
    }  
  }
  return 0;
}
