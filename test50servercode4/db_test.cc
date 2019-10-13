#include "db.hpp"

void TestBlogTable()
{
    Json::StyledWriter writer;

    MYSQL* mysql=blog_system::MySQLInit();
    blog_system::BlogTable blog_table(mysql);
    Json::Value blog;
    bool ret=false;
    #if 0
    //测试插入 
    blog["title"]="我的第33博客";
    blog["content"]="我要拿30w年薪";
    blog["tag_id"]=1;
    blog["create_time"]="2019/07/28";
    bool ret=blog_table.Insert(blog);
    printf("insert:%d\n",ret);
    blog_system::MySQLRelease(mysql);
    #endif

    #if 0
    Json::Value blogs;
    ret=blog_table.SelectAll(&blogs);
    printf("select all %d\n",ret);
    printf("blogs:%s\n",writer.write(blogs).c_str());
    #endif

    #if 0
    Json::Value blogs;
    ret=blog_table.SelectOne(3,&blogs);
    printf("select one %d\n",ret);
    printf("blogs:%s\n",writer.write(blogs).c_str());
    #endif

    #if 0
    blog["blog_id"]=1;
    blog["title"]="小马过河";
    blog["content"]="小飞机";
     
    ret=blog_table.Update(blog);
    printf("update %d\n",ret);
    printf("blog:%s\n",writer.write(blog).c_str());
    #endif
    ret=blog_table.Delete(3);
    
}

void TestTagTable()
{
    Json::StyledWriter writer;
    Json::Value tag;
    bool ret=false;
    MYSQL* mysql=blog_system::MySQLInit();
    blog_system::TagTable tag_table(mysql);

    //测试插入
    tag["tag_name"]="c语言";
    ret=tag_table.Insert(tag);
    printf("insert %d\n",ret);

}

int  main()
{
    //TestBlogTable();
    TestTagTable();
    return 0;
}