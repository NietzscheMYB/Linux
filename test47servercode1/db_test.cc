#include"db.hpp"

void TestBlogTable()
{
    Json::StyledWriter writer;

    MYSQL* mysql=blog_system::MySQLInit();
    blog_system::BlogTable blog_table(mysql);
    Json::Value blog;
     
    blog["title"]="我的第一批博客";
    blog["content"]="我要拿30w年薪";
    blog["tag_id"]=1;
    blog["create_time"]="2019/07/28";
    bool ret=blog_table.Insert(blog);
    printf("insert:%d\n",ret);
    blog_system::MySQLRelease(mysql);
    

}
int  main()
{
    TestBlogTable();
    return 0;
}