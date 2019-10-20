#if 0
//通过使用mysql api实现数据库插入功能
#include<cstdio>
#include<cstdlib>
//默认从usr/include目录中查找头文件，
//所以搞清路径的关系
#include<mysql/mysql.h>
int main()
{
    //1.创建一个数据库连接句柄（句柄遥控器）
    MYSQL* connect_fd=mysql_init(NULL);
    //2.和数据库建立连接（和tcp区分开，在应用层建立连接）
    //从应用层角度建立连接
    //连接过程需要指定一些必要的信息
    //  a.连接句柄
    //  b.服务器ip地址
    //  c.用户名
    //  d.密码
    //  e.数据库名blog_system
    //  f.服务器的端口号
    //  g.unix_sock NULL
    //  h.client_flag 0

    //这个函数返回值是一个是否成或者失败
    if(mysql_real_connect(connect_fd,"127.0.0.1","root","myb102382","blog_system",3306,NULL,0))
    {
        printf("连接失败！%s888\n",mysql_error(connect_fd));
        mysql_close(connect_fd);
        return 1;
    }
    printf("连接成功！\n");
    //3.设计编码方式
    // mysql server部分最初安装的时候已经设置成立utf8
    //也得在客户端这边也设置成utf8
    mysql_set_character_set(connect_fd,"utf8");
    //4.拼接sql语句
    char sql[1024*4]={0};
    char title[]="立一个flag";
    char content[]="我要拿30w年薪";
    int tag_id=1;
    char date[]="2019/07/25";
    sprintf(sql,"insert into blog_table values(null,'%s','%s',%d,'%s')",title,
    content,tag_id,date);//拼接
    //5.让数据库执行sql
    int ret=mysql_query(connect_fd,sql);
    if(ret<0)
    {
        printf("执行sql失败！%s\n",mysql_error(connect_fd));
        mysql_close(connect_fd);//也要close
        return 1;
    }
    printf("插入成功！\n");
    //断开连接！
    mysql_close(connect_fd);
    return 0;
}
#endif

//通过这个程序使用MYsql api实现数据插入的功能
#include<cstdio>
#include<cstdlib>
//默认从/usr/include目录中查找头文件，mysql.h
#include<mysql/mysql.h>  //编译器默认在inclue中找头文件，所以搞清路径关系
int main()
{
    //1.创建一个数据库连接句柄（句柄遥控器）
    MYSQL* connect_fd=mysql_init(NULL);
    //2.和数据库建立连接(和TCP的区分开，在应用层建立连接)     从应用层角度建立连接
    //连接过程需要指定一些必要的信息
    //              a.链接句柄
    //              b.服务器ip地址
    //              c.用户名
    //              d.密码
    //              e.数据库名blog_system 
    //              f.服务器的端口号
    //              g. unix_sock NULL
    //              h.client_flag 0
    //netstat -anp |grep 3306   //mysql对应的端口号
    //这个函数返回值是一个是否成功或者失败
    if(mysql_real_connect(connect_fd,"127.0.0.1","root","myb102382","blog_system",3306,NULL,0)==NULL)
    {
        printf("链接失败！%s\n",mysql_error(connect_fd));
        mysql_close(connect_fd);    
        return 1;
    }
    printf("链接成功！\n");
    //3.设置编码方式
    //   mysql server部分最初安装的时候已经设置成了 utf8
    //   也得在客户端这边也设置成utf8
    mysql_set_character_set(connect_fd,"utf8");
    //4.拼接SQL语句
    char sql[1024*4]={0};
    char title[]="立一个flag";
    char content[]="我要拿30w年薪";
    int tag_id=1;
    char date[]="2019/07/25";
    sprintf(sql,"insert into blog_system values(null,'%s','%s',%d,'%s')",title,content,tag_id,date);
    printf("sql:%s\n",sql);//大于sql语句
    //5.让数据库服务器执行sql
    int ret=mysql_query(connect_fd,sql);
    if(ret<0)
    {
        printf("执行sql失败！ %s\n",mysql_error(connect_fd));
        mysql_close(connect_fd);//也要掉close
        return 1;
    }
    if(ret>=0)
    {
      printf("插入成功\n");
    }
   // printf("插入成功！\n");  
    //断开连接！！
    mysql_close(connect_fd);
    return 0;
}
