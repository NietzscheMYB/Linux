#include"show.hpp"
#include"student.hpp"
void menu()
{
  cout<<"===================================="<<endl;
  cout<<"===================================="<<endl;
  cout<<"=========欢迎登陆图书系统==========="<<endl;
  cout<<"===================================="<<endl;
  cout<<"==============1.进入================"<<endl;
  cout<<"==============2.退出================"<<endl;
  cout<<"===================================="<<endl;
}

void table1()
{
  cout<<"===================================="<<endl;
  cout<<"=============1.注册================="<<endl;
  cout<<"=============2.登录================="<<endl;
  cout<<"===================================="<<endl;
  cout<<"===================================="<<endl;
}
void table1fun(StudentTable&st,BookTable& bt)
{
    int flag2=0;
    cin>>flag2;
    switch (flag2)
    {
    case 1: table2();table2fun(st);break;
    case 2:table3();assert(table3fun(st,bt)); break;
    default:
        break;
    }
}


void table2()
{
  cout<<"请输入学号,姓名,班级,密码"<<endl;
}
void table2fun(StudentTable&st)
{
        Student s;
        cin>>s._id>>s._name>>s._class>>s._password;
        st.Insert(&s);
}

void table3()
{
  cout<<"请输入姓名与密码"<<endl;
}
bool table3fun(StudentTable&st,BookTable& bt)
{
    Student s;
    cin>>s._name>>s._password;
    if(st.Find(s))
    {
        while(1)
        {
            table4();
            int flag=0;
            cin>>flag;
            switch (flag)
            {
            case 1:
                /* code */
                break;
            case 2:break;
            case 3:table4fun3(bt);break;
            case 4:return true;
            default:cout<<"输入错误请重新输入!"<<endl;
                break;
            }
        }
        return true;
    }
    return false;
}



void table4()
{
  cout<<"==================================="<<endl;
  cout<<"=======1.查看借阅图书==============="<<endl;
  cout<<"=======2.归还图书==================="<<endl;
  cout<<"=======3.搜索图书==================="<<endl;
  cout<<"=======4.返回======================="<<endl;
   
}

void table4fun3(BookTable& bt)
{
    string bookname;
    cout<<"请输入书名"<<endl;
    cin>>bookname;
    bt.Find(&bookname);
}