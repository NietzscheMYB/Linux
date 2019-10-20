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
        //转义是为了防止在拼接的时候‘’出现错误的理解！！
        mysql_real_escape_string(mysql_,to.get(),content.c_str(),content.size());
        //核心就是拼装sql语句
        //防止正文过长
        //采用智能指针
        std::unique_ptr<char> sql(new char[content.size()*2+4096]);
        sprintf(sql.get(),"insert into blog_table values(null,'%s','%s',%d,'%s')",
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
    //blogs作为一个输出型参数
    bool SelectAll(Json::Value* blogs,const std::string&tag_id="")
    {
        //查找不需要太长的sql，固定长度就行
        char sql[1024*4]={0};
        if(tag_id=="")
        {
            //此时不需要按照tag来筛选结果
            sprintf(sql,"select blog_id,title,tag_id,create_time from blog_table");
        }else
        {
            //此时需要按照tag来筛选
            sprintf(sql,"select blog_id,title,tag_id,create_time from blog_table where tag_id=%d",std::stoi(tag_id)); 
        }
        int ret=mysql_query(mysql_,sql);
        if(ret!=0)
        {
            printf("执行查找所有博客失败!%s\n",mysql_error);
            return false;
        }
        printf("执行查找所有博客成功!\n");
        //获取结果集合
        MYSQL_RES* result=mysql_store_result(mysql_);
        //获取每行
        int rows=mysql_num_rows(result);
        
        //遍历结果集合然后把结果写到bolgs参数中，返回调用者
        for(int i=0;i<rows;i++)
        {
            MYSQL_ROW row=mysql_fetch_row(result);
            Json::Value blog;
            //row[]中的下标和上面select语句中写的列的
            //顺序是相关的
            blog["blog_id"]=atoi(row[0]);
            blog["title"]=row[1];
            blog["tag_id"]=atoi(row[2]);
            blog["create_time"]=row[3];
            //将每一行信息写道blogs中
            blogs->append(blog);
        }
        //mysql查询的结果需要
        mysql_free_result(result);
        printf("执行查找所有博客成功！共查找到%d条\n",rows);
        return true;
    }
    //blog同样是输出型参数，根据当前的blog_id在数据库中找到具体的内容
    bool SelectOne(int32_t blog_id,Json::Value* blog)
    {
        char sql[1024]={0};
        sprintf(sql,"select blog_id,title,content,tag_id,create_time from blog_table where blog_id=%d",blog_id);
        int ret=mysql_query(mysql_,sql);
        if(ret!=0)
        {
            printf("执行查找结果失败!%s\n",mysql_error);
            return false;
        }
        MYSQL_RES* result=mysql_store_result(mysql_);
        int rows=mysql_num_rows(result);
        if(rows!=1)
        {
            printf("查找到的博客不是只有一条!实际有%d条\n",rows);
            return false;
        }
        MYSQL_ROW row=mysql_fetch_row(result);
        (*blog)["blog_id"]=atoi(row[0]);
        (*blog)["title"]=row[1];
        (*blog)["content"]=(row[2]);
        (*blog)["tag_id"]=atoi(row[3]);
        (*blog)["create_time"]=row[4];
        return true;
    }
    bool Update(const Json::Value& blog)
    {
        //先进行转义！
        const std::string& content=blog["content"].asString();
        //为啥to的长度是2*size+1 这是文档的要求
        std::unique_ptr<char> to(new char[content.size()*2+1]);

        //第一个参数是句柄，第二个参数是to，第三个参数是from，第四个参数是from的长度
        mysql_real_escape_string(mysql_,to.get(),content.c_str(),content.size());

        //核心就是拼装sql语句
        //防止正文过长
        std::unique_ptr<char> sql(new char[content.size()*2+4096]);
        sprintf(sql.get(),"update blog_table set title='%s',content='%s',tag_id=%d where blog_id=%d",
            blog["title"].asCString(),
            to.get(),
            blog["tag_id"].asInt(),
            blog["blog_id"].asInt());
        int ret=mysql_query(mysql_,sql.get());
        if(ret!=0)
        {
            printf("更新博客失败!%s\n",mysql_error(mysql_));
            return false;
        }    
        printf("更新博客成功！\n");
        return true;
    }
    bool Delete(int32_t blog_id)
    {
        char sql[1024*4]={0};
        sprintf(sql,"delete from blog_table where blog_id=%d",blog_id);
        int ret =mysql_query(mysql_,sql);
        if(ret!=0)
        {
            printf("删除博客失败!%s\n",mysql_error(mysql_));
            return false;
        }
        return true;
    }
private:
    MYSQL* mysql_;
}; 

//用几个表，建几个类
class TagTable
{
public:
TagTable(MYSQL* mysql)
:mysql_(mysql)
{}
bool Insert(const Json::Value& tag)
{
    char sql[1024*4];
    sprintf(sql,"insert into tag_table values(null,'%s')",
        tag["tag_name"].asCString());
    int ret=mysql_query(mysql_,sql);
    if(ret!=0)
    {
        printf("插入标签失败！%s\n",mysql_error(mysql_));
        return false;
    }
    printf("插入标签成功!\n");
    return true;
}
bool Delete(int32_t tag_id)
{
    char sql[1024*4]={0};
    sprintf(sql,"delete from tag_table where tag_id=%d",tag_id);
    int ret=mysql_query(mysql_,sql);
    if(ret!=0)
    {
        printf("删除标签失败!%s\n",mysql_error(mysql_));
        return false;
    }
    printf("删除标签成功!\n");
    return true;
}
bool SelectAll(Json::Value* tags)
{
    char sql[1024*4]={0};
    sprintf(sql,"select tag_id,tag_name from tag_table");

    int ret=mysql_query(mysql_,sql);
    if(ret!=0)
    {
        printf("查找标签失败!%s\n",mysql_error(mysql_));
        return false;
    }
    MYSQL_RES* result=mysql_store_result(mysql_);
    int rows=mysql_num_rows(result);
    for(int i=0;i<rows;i++)
    {
        MYSQL_ROW row=mysql_fetch_row(result);
        Json::Value tag;
        tag["tag_id"]=atoi(row[0]);
        tag["tag_name"]=row[1];
        tags->append(tag);
    }
    printf("查找标签成功!共找到%d个!\n",rows);
    return true;
}
private:
MYSQL* mysql_;
};





}//end blog_system
