//创建一些相关的类来封装数据库操作

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<memory>
#include<mysql/mysql.h>
#include<jsoncpp/json/json.h>

namespace blog_system
{
static MYSQL* MySQLInit()
{
    //初始化mysql句柄，并建立连接
    //1.创建一个句柄
    MYSQL* connect_fd=mysql_init(NULL);
    //2.建立数据库连接
    if(mysql_real_connect(connect_fd,"127.0.0.1","root","myb102382","blog_system",3306,NULL,0)==NULL)
    {
        printf("连接失败!%s\n",mysql_error(connect_fd));
        mysql_close(connect_fd);
       //// return ;
    }
    //3.设定字符编码
    mysql_set_character_set(connect_fd,"utf8");
    return connect_fd;
}
static void MySQLRelease(MYSQL* connect_fd)
{
    //释放句柄，并断开连接
    mysql_close(connect_fd);
}
//创建一个类，用于操作博客表的类
class BlogTable
{
public:
    BlogTable(MYSQL* connect_fd)
    :mysql_(connect_fd)
    {
        //通过这个构造函数获取到一个数据库的操作句柄
    }
    //以下操作相关参数都是统一使用Json格式
    //Json：：Value jsoncpp中最核心的类
    //Json::Value 就表示一个具体的json对象
    //形如
    //{title:"博客标题"
    //content:"博客正文"
    //create_time:"创建时间"
    //tag_id:"标签id"
    //}    
    //最大的好处是方便扩展
    bool Insert(const Json::Value& blog)
    {
        const std::string& content=blog["content"].asString();
        //为啥to的长度是2*size+1,这是文档的要求
        //借用智能指针，就不用手动delete释放
        std::unique_ptr<char> to(new char[content.size()*2+1]);
        //第一个参数是句柄，第二个参数是to，第三个参数是from，第四参数是from的长度
        //to现在已经转义了！！
        mysql_real_escape_string(mysql_,to.get(),content.c_str(),content.size());
        //核心就是拼装sql语句
        //防止正文过长
        //采用智能指针
        std::unique_ptr<char> sql(new char[content.size()*2+4096]);
        sprintf(sql.get(),"insert into blog_system(null,'%s','%s',%d,'%s')",
                blog["title"].asCString(),
                to.get(),
                blog["tag_id"].asInt(),
                blog["create_time"].asCString());
        //让数据库服务执行sql
        int ret=mysql_query(mysql_,sql.get());
        if(ret!=0)
        {
            printf("执行插入博客系统失败!%s\n",mysql_error(mysql_));
            return false;
        }
        printf("执行插入结果成功！\n");
        return true;

    }
private:
    MYSQL* mysql_;
}; 






}//end blog_system
