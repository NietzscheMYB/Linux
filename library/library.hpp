#pragma once
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<assert.h>
#include<mysql/mysql.h>
#include<memory>
#include<vector>
using namespace std;

static MYSQL* MySQLInit()
{
  //初始化mysql句柄，并建立连接
  ////1.创建一个句柄
  MYSQL* connect_fd=mysql_init(NULL);
  //2.建立数据库连接
  if(mysql_real_connect(connect_fd,"127.0.0.1","root","myb102382","library",3306,NULL,0)==NULL)
  {
    printf("连接失败!%s\n",mysql_error(connect_fd));
    mysql_close(connect_fd);
  }
  //3.设定字符编码
  mysql_set_character_set(connect_fd,"utf8");
  return connect_fd;
}

static void MySQLRelease(MYSQL* connect_fd)
{
  //释放句柄，断开连接
  mysql_close(connect_fd);
}

struct Book
{
  Book()
  {

  }
  Book(int id,string name,string author,string press,string type,string location,string status)
   : _id(id)
    ,_name(name)
   ,_author(author)
   ,_press(press)
   ,_type(type)
   ,_location(location)
   ,_status(status)
  {

  }

  int _id=0;
  string _name;
  string _author;
  string _press;
  string _type;
  string _location;
  string _status="未借阅";
};

struct Student
{
  Student()
  {}

  Student(int id,string name,string classs,string password)
  {
    _id=id;
    _name=name;
    _class=classs;
    _password=password;
  }

  int _id;
  string _name;
  string _class;
  int book_id=0;
  string _password;
};

struct Teacher
{
  Teacher()
  {}
  Teacher(int id,string name,string college,string password)
  {
    _id=id;
    _name=name;
    _college=college;
    _password=password;
  }
  int _id;
  string _name;
  string _college;
  string _password;
};



class BookTable
{
public:
  BookTable(MYSQL* connect_fd)
  :mysql_(connect_fd)
  {}
  bool Insert(Book* value)
  {
    unique_ptr<char> sql(new char[1024]);
    sprintf(sql.get(),"insert into BookTable values(%d,'%s','%s','%s','%s','%s','%s')",
        value->_id,
        value->_name.c_str(),
        value->_author.c_str(),
        value->_press.c_str(),
        value->_type.c_str(),
        value->_location.c_str(),
        value->_status.c_str()
        );
    //让数据库执行sql
    int ret=mysql_query(mysql_,sql.get());
    if(ret!=0)
    {
        printf("执行插入数据失败!%s\n",mysql_error(mysql_));
        return false;
    }
    printf("执行插入结果成功!\n");
    return true;
  }
  bool SelectAll()
  {
    char sql[1024]={0};
    sprintf(sql,"select * from BookTable");
    int ret=mysql_query(mysql_,sql);
    if(ret!=0)
    {
      printf("查询失败!%s\n",mysql_error(mysql_));
      return false;
    }
    printf("查找所有书籍成功!\n");
    //获取结果结合
    MYSQL_RES* result=mysql_store_result(mysql_);
    //获取每行
    int rows=mysql_num_rows(result);

    for(int i=0;i<rows;i++)
    {
      MYSQL_ROW row=mysql_fetch_row(result);
      printf("序号:%d 书名:%s 作者:%s 出版社:%s 类型:%s 位置:%s 借阅情况:%s\n",atoi(row[0]),row[1],row[2],row[3],row[4],row[5],row[6]);
    }
    mysql_free_result(result);

    return true;
  }

  bool Find(string* name)
  {
    char sql[1024]={0};
    sprintf(sql,"select id,author,press,type,location,status from BookTable where name='%s'",name->c_str());

    int ret=mysql_query(mysql_,sql);
    if(ret!=0)
    {
      printf("未找到该书籍!%s\n",mysql_error(mysql_));
      return false;
    }
    printf("查找该书籍成功!\n");
    //获取结果集合
    MYSQL_RES* result=mysql_store_result(mysql_);
    //获取每行
    int rows=mysql_num_rows(result);

    for(int i=0;i<rows;i++)
    {
      MYSQL_ROW row=mysql_fetch_row(result);
      printf("序号:%d 作者:%s 出版社:%s 类型:%s 位置:%s 借阅状态:%s\n",atoi(row[0]),row[1],row[2],row[3],row[4],row[5]);
    }
  
    mysql_free_result(result);
    return true;
  
  }
  int Retid(string* name)
  {
        char sql[1024]={0};
    sprintf(sql,"select id,author,press,type,location,status from BookTable where name='%s'",name->c_str());

    int ret=mysql_query(mysql_,sql);
    if(ret!=0)
    {
      printf("未找到该书籍!%s\n",mysql_error(mysql_));
      return false;
    }
    //printf("查找该书籍成功!\n");
    //获取结果集合
    MYSQL_RES* result=mysql_store_result(mysql_);
    //获取每行
    int rows=mysql_num_rows(result);
      MYSQL_ROW row=mysql_fetch_row(result);
    
    mysql_free_result(result);
      return atoi(row[0]);
  }
  bool Update(Book* value)
  {
    unique_ptr<char> sql(new char[1024]);
    sprintf(sql.get(),"update BookTable set name='%s',author='%s',press='%s',type='%s',location='%s' where id=%d ",value->_name.c_str(),value->_author.c_str(),value->_press.c_str(),value->_type.c_str(),value->_location.c_str(),value->_id);
    int ret=mysql_query(mysql_,sql.get());
    if(ret!=0)
    {
      printf("更新失败!%s\n",mysql_error(mysql_));
      return false;
    }
    printf("更新成功!\n");
    
    return true;
  }

  bool CheckStatus(int id,string* name)
  {
    char sql[1024]={0};
    sprintf(sql,"select * from BookTable where name='%s'&&id=%d &&status='未借阅'",name->c_str(),id);

    int ret=mysql_query(mysql_,sql);
    if(ret!=0)
    {
      printf("未找到该书籍!%s\n",mysql_error(mysql_));
      return false;
    }
    //获取结果集合
    MYSQL_RES* result=mysql_store_result(mysql_);
    //获取每行
    int rows=mysql_num_rows(result);
    if(rows==0)
    {
      printf("没有找到相应的书籍!\n");
      mysql_free_result(result);
      return false;
    }
    mysql_free_result(result);
    return true;
  }


  bool Borrow(int id,string* name)
  {
    if(Find(name)&&CheckStatus(id,name))
    {
            

            unique_ptr<char> sql(new char[1024]);
            std::string status="已借阅";
            sprintf(sql.get(),"update BookTable set status='%s' where id=%d&&name='%s'",status.c_str(),id,name->c_str());
          int ret=mysql_query(mysql_,sql.get());
          if(ret!=0)
          {
            printf("借阅失败!%s\n",mysql_error(mysql_));
            return false;
          } 
         //printf("借阅成功!\n");
      return true;
    }
    return false;
  }
  bool Delete(Book* value)
  {
    char sql[1024]={0};
sprintf(sql,"delete from BookTable where name='%s'&&id=%d",value->_name.c_str(),value->_id);
    int ret=mysql_query(mysql_,sql);
    if(ret!=0)
    {
      printf("删除失败!%s\n",mysql_error(mysql_));
      return false;
    }
    printf("删除成功!\n");
    return true;
  }
  bool Return(int id,string* name)
  {
     unique_ptr<char> sql(new char[1024]);
     string status="未借阅";
    sprintf(sql.get(),"update BookTable set status='%s' where id=%d&&name='%s' ",status.c_str(),id,name->c_str());
    int ret=mysql_query(mysql_,sql.get());
    if(ret!=0)
    {
      printf("归还失败!%s\n",mysql_error(mysql_));
      return false;
    }
    printf("归还成功!\n");
    return true;
  }
  bool Sort()
  {
    char sql[1024]={0};
    sprintf(sql,"select name,author,press,type,location from BookTable order by id");
    int ret=mysql_query(mysql_,sql);
    if(ret!=0)
    {
      printf("排序失败!\n%s",mysql_error(mysql_));
      return false;
    }
    printf("排序成功!\n");
          //获取结果集合
        MYSQL_RES* result=mysql_store_result(mysql_);
      //获取每行
      int rows=mysql_num_rows(result);

      for(int i=0;i<rows;i++)
      {
        MYSQL_ROW row=mysql_fetch_row(result);
        printf("书名:%s 作者:%s 出版社:%s 类型:%s 位置:%s\n",(row[0]),row[1],row[2],row[3],(row[4]));
      }
    return true;
  }

private:
  MYSQL* mysql_;
};






