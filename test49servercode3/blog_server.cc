#include"httplib.h"
#include<iostream>
#include<cstdio>
#include<signal.h>

using namespace std;


#include"db.hpp"

MYSQL* mysql=NULL;

int main()
{
   //命名空间
    using namespace httplib;
    using namespace blog_system;
    //1.先和数据库建立好连接
    mysql=blog_system::MySQLInit();
    signal(SIGINT,[](int signo){
        blog_system::MySQLRelease(mysql);
        exit(0);
        });
  //2.创建相关数据库处理对象
    BlogTable blog_table(mysql);
    TagTable tag_tabel(mysql);
  //3.创建服务器，并设置“路由”http服务器中的路由，此处的路由指的是 把方法+path映射到那个处理函数，关联关系声明清楚
    
    Server server;
    //创建一个新博客
    server.Post("/blog",[](const Request& req,Response& resp){
      printf("新增博客!\n");
      //1.获取到请求中body 并解析json
      Json::Reader reader;
      Json::FastWriter writer;
      Json::Value req_json;
      Json::Value resp_json;
      bool ret=reader.parse(req.body,req_json);
      if(!ret)
      {
        //解析出错，给用户提醒
        printf("解析请求失败！%s\n",req.body.c_str());
        //构造一个响应对象，告诉客户端出错了
        resp_json["ok"]=false;    //这样写是因为当时规定的ok返回true
        resp_json["reason"]="input data parse error!";
        resp.status=400;//设置状态码，客户端请求解析出错
        resp.set_content(writer.write(resp_json),"application/json");
        
        return ;


      }


    });
    //获取所有博客
    server.Get("/blog",[](const Request& req,Response& resp){
        
    });
    //查看某个博客
    //这样写是为了识别那个id，
    server.Get(R"(/blog/(\d+)",[](const Request& req,Response& resp)
    {

    });
    //修该某个博客
    server.Put(R"(/blog/(\d+))",[](const Request& req,Response& resp){

    });
    //删除
    server.Delete(R"(/blog/(\d+))",[](const Request& req,Response& resp){

    });
    //新增标签
    server.Post("/tag",[](const Request& req,Response& resp){

    });
    //查看所有标签
    server.Get("/tag",[](const Request& req,Response& resp){

    });
    //删除标签
    server.Delete(R"(/tag/(\d+))",[](const Request& req,Response& resp){

    });

    server.set_base_dir("./wwwroot");

    //启动服务器
    server.listen("0.0.0.0",9093);

    return 0;
}
