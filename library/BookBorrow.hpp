#pragma once
#include"library.hpp"


class BookBorrowTable
{
public:
  BookBorrowTable(MYSQL* connect_fd)
    :mysql_(connect_fd)
  { }
  
    //借阅则插入
    bool Insert(int bookid,string* username,string* bookname)
    {
        unique_ptr<char> sql(new char[1024]);
        sprintf(sql.get(),"insert into BookBorrow values(%d,'%s','%s')",
        bookid,
        username->c_str(),
        bookname->c_str()
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
    bool Delete(int bookid,string* username,string* bookname)
    {
        char sql[1024]={0};
        sprintf(sql,"delete from BookBorrow where bookname='%s'&&bookid=%d&&username='%s'",bookname->c_str(),bookid,username->c_str());
        int ret=mysql_query(mysql_,sql);
        if(ret!=0)
        {
           printf("删除失败!%s\n",mysql_error(mysql_));
           return false;
        }
        printf("删除成功!\n");
        return true;
    }
    


private:
MYSQL* mysql_;
};