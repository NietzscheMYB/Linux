#pragma once
#include"library.hpp"


class StudentTable
{
public:
  StudentTable(MYSQL* connect_fd)
    :mysql_(connect_fd)
  { }
  bool Insert(Student* data)
  {
    unique_ptr<char> sql(new char[1024]);
    sprintf(sql.get(),"insert into StudentTable values(%d,'%s','%s',%d,'%s')",
        data->_id,
        data->_name.c_str(),
        data->_class.c_str(),
        data->book_id,
        data->_password.c_str());
    //让数据库执行sql
    int ret=mysql_query(mysql_,sql.get());
    if(ret!=0)
    {
        printf("执行插入数据失败!%s\n",mysql_error(mysql_));
        return false;
    }
    printf("注册成功!\n");

    return true;
  }
  bool UpdateBorrow(int bookid,string*name)
  {
     unique_ptr<char> sql(new char[1024]);
    sprintf(sql.get(),"update StudentTable set book_id=%d where name='%s'",bookid,name->c_str());
    //让数据库执行sql
    int ret=mysql_query(mysql_,sql.get());
    if(ret!=0)
    {
        printf("更新bookid失败!%s\n",mysql_error(mysql_));
        return false;
    }
    printf("更新bookid成功!\n");
 
    return true;
  }
  bool Find(Student&s)
  {
    unique_ptr<char> sql(new char[1024]);
    sprintf(sql.get(),"select * from StudentTable where name='%s'&&password='%s'",s._name.c_str(),s._password.c_str());
    int ret=mysql_query(mysql_,sql.get());
    if(ret!=0)
    {
      printf("用户不存在!%s\n",mysql_error(mysql_));
      return false;
    }
    printf("登录成功!\n");
    //获取结果结合
    MYSQL_RES* result=mysql_store_result(mysql_);
    //获取每行

    mysql_free_result(result);
    return true;
  }

private:
MYSQL* mysql_;
};

#if 0
class Studentuser{
  public:
    Studentuser(Student s,MYSQL* connect_fd)
      :_s(s)
       ,mysql_(connect_fd)
       ,bt(mysql_)
       ,st(mysql_)
    {

    }
    bool FindBook(string name)
    {
      bt.Find(&name);
      return true;
    }
   bool CheckSelf(Student& s)
   {
      if(st.Find(s))
      {
        printf("登录成功!\n");
         return true;
      }
      return false;
   }

    bool BorrowBook(string name)
    {
      if(FindBook(name))
      {
        bt.Borrow(&name);
        int id=bt.Retid(&name);
        st.UpdateBorrow(id,&name);
        return true;
      }
      return false;
    }


  private:
    Student _s;
    MYSQL* mysql_;
    BookTable bt;
    StudentTable st;
};
#endif