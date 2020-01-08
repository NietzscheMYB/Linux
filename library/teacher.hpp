#pragma once
#include"library.hpp"
#include"BookBorrow.hpp"


class TeacherTable
{
public:
  TeacherTable(MYSQL* connect_fd)
    :mysql_(connect_fd)
  { }
  //老师注册！！
  bool Insert(Teacher* data)
  {
    unique_ptr<char> sql(new char[1024]);
    sprintf(sql.get(),"insert into TeacherTable values(%d,'%s','%s','%s')",
        data->_id,
        data->_name.c_str(),
        data->_college.c_str(),
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

  //老师借书
  bool TeacherBorrow(int bookid,string*name,Teacher s)
  {
    //先对booktable进行操作！！
    BookTable bt(mysql_);
    if(bt.Borrow(bookid,name))
    {
         //再对StuentTable操作
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
         
         //再对BookBorrow操作！！
         BookBorrowTable bb(mysql_);
         bb.Insert(bookid,&s._name,name);    
         return true;
    }
    return false;
    
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

  //老师验证
  bool CheckSelf(Teacher&s)
  {
    unique_ptr<char> sql(new char[1024]);
    sprintf(sql.get(),"select * from TeacherTable where name='%s'&&password='%s'",s._name.c_str(),s._password.c_str());
    int ret=mysql_query(mysql_,sql.get());
    if(ret!=0)
    {
      printf("用户不存在!%s\n",mysql_error(mysql_));
     // mysql_free_result(result);
      return false;
    }
    
    //获取结果结合
    MYSQL_RES* result=mysql_store_result(mysql_);
    //获取每行
    int rows=mysql_num_rows(result);
    if(rows==0)
    {
      printf("登录失败!\n");
      mysql_free_result(result);
      return false;
    }
    mysql_free_result(result);
    printf("登录成功!\n");
    return true;
  }
  //老师还书
  bool ReturnBook(int bookid,string* name,Teacher&s)
  {
    //先对BookBorrow操作!!
    BookBorrowTable bb(mysql_);
    bb.Delete(bookid,&s._name,name);    

    #if 0
    //再对StudentTable操作！
    unique_ptr<char> sql(new char[1024]);
    sprintf(sql.get(),"update TeacherTable set book_id=0 where book_id=%d&&name='%s'",bookid,name->c_str());
    //让数据库执行sql
    int ret=mysql_query(mysql_,sql.get());
    if(ret!=0)
    {
        printf("更新bookid失败!%s\n",mysql_error(mysql_));
        return false;
    }
    printf("更新bookid成功!\n");
    #endif

    //再对 BookTable操作
    BookTable bt(mysql_);
    bt.Return(bookid,name);

    return true;
  }
  bool FindBook(string*name)
  {
    //直接对BookStable进行操作！！
    BookTable bt(mysql_);
    return bt.Find(name);
  }


  bool LookBorrow(string&name)
  {
    BookBorrowTable bb(mysql_);
    char sql[1024]={0};
    sprintf(sql,"select * from BookBorrow where username='%s'",name.c_str());
    int ret=mysql_query(mysql_,sql);
    if(ret!=0)
    {
      printf("查询失败!%s\n",mysql_error(mysql_));
      return false;
    }
    //printf("查找所有书籍成功!\n");
    //获取结果结合
    MYSQL_RES* result=mysql_store_result(mysql_);
    //获取每行
    int rows=mysql_num_rows(result);
    if(rows==0)
    {
      printf("未借阅图书!\n");
      return true;
    } 
    for(int i=0;i<rows;i++)
    {
      MYSQL_ROW row=mysql_fetch_row(result);
      printf("序号:%d 借阅者:%s 书名:%s ",atoi(row[0]),row[1],row[2]);
    }
    mysql_free_result(result);
  }
private:
MYSQL* mysql_;
};

