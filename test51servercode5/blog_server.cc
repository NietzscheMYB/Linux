#include"httplib.h"
#include<iostream>
#include<cstdio>
#include<signal.h>
#include"db.hpp"
using namespace std;

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
    printf("服务启动成功!\n");
  //2.创建相关数据库处理对象
    BlogTable blog_table(mysql);
    
    TagTable tag_tabel(mysql);
  //3.创建服务器，并设置“路由”http服务器中的路由，此处的路由指的是 把方法+path映射到那个处理函数，关联关系声明清楚
    
    Server server;
    //创建一个新博客
    server.Post("/blog",[&blog_table](const Request& req,Response& resp){
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
      //2.对参数进行校验
      if(req_json["title"].empty()||req_json["content"].empty()||req_json["create_time"].empty()
        ||req_json["tag_id"].empty())
      {
        //检验出错，将错误返回给用户
        printf("参数检验失败!%s\n",req.body.c_str());
        //构造响应对象，告诉客户端出错
        resp_json["ok"]=false;
        resp_json["reason"]="input data format error";
        resp.status=400;
        resp.set_content(writer.write(resp_json),"application/json");
        return ;
      }
      //3.真的调用mysql来操作
      ret=blog_table.Insert(req_json);
      if(!ret)
      {
        printf("博客插入失败！\n");
        //构造一个响应对象，告诉客户端出错
        resp_json["ok"]=false;
        resp_json["reason"]="blog insert failed";
        resp.status=500;
        //将json变成字符串返回给客户
        resp.set_content(writer.write(resp_json),"application/json");
      }
      //插入成功，将正确信息返回给客户端
      printf("插入成功!\n");
      resp_json["ok"]=true;
      resp.set_content(writer.write(resp_json),"application/json");
      return ;

    });
    
    //获取所有博客
    server.Get("/blog",[&blog_table](const Request& req,Response& resp){
       
        printf("获取所有博客！");
        //1.尝试获取tag_id 标签，tag_id 存在querystring中 querystring是个键值对，如果tag_id 不存在则返回一个空字符
        const std::string& tag_id=req.get_param_value("tag_id");
        //就不想解析请求了，也不需要合法判定
        //2.调用数据库操作所有博客结果
        Json::Value resp_json;
        Json::FastWriter writer;
        bool ret=blog_table.SelectAll(&resp_json,tag_id);
        if(!ret)
        {
          resp_json["ok"]=false;
          resp_json["reason"]="select all failed";
          resp.status=500;
          resp.set_content(writer.write(resp_json),"application/json");
          return ;
        }
        //3.构造正确响应结果
        resp.set_content(writer.write(resp_json),"application/json");
        return ;
    });


    //查看某个博客
    //这样写是为了识别那个id，
    server.Get(R"(/blog/(\d+))",[&blog_table](const Request& req,Response& resp)
    {
        //1.解析获取blog id     
        int32_t blog_id=std::stoi(req.matches[1].str());
        printf("查看id为%d的博客\n",blog_id);
        //2.直接操作mysql
        Json::Value resp_josn;
        Json::FastWriter writer;
        bool ret=blog_table.SelectOne(blog_id,&resp_josn);
        if(!ret)
        {
          //构造返回信息给客户，
          resp_josn["ok"]=false;
          resp_josn["reason"]="error id 查找指定博客失败";
          resp.status=404;//没有找到指定资源
          //将json对象返回给用户
          resp.set_content(writer.write(resp_josn),"application/json");
          return ;
        }
        //查找成功
        printf("查找成功");
        //3.构造一个正确的信息返回给用户
        resp.set_content(writer.write(resp_josn),"application/json");
        return ;
    });

    //修该某个博客
    server.Put(R"(/blog/(\d+))",[&blog_table](const Request& req,Response& resp){
        //1.先获取到博客id
        int32_t blog_id=std::stoi(req.matches[1].str());
        printf("修改id为%d的博客\n",blog_id);
        //获取请求并解析结构
        Json::Value req_json;
        Json::Value resp_json;
        Json::FastWriter writer;
        Json::Reader reader;
        //将字符串解析为json
        bool ret=reader.parse(req.body,req_json);
        if(!ret)
        {
          //解析出错，构造错误信息，返回给客户端
          resp_json["ok"]=false;
          resp_json["reason"]="update blog pares request failed";
          resp.status=400;
          //将json转换位字符串
          resp.set_content(writer.write(resp_json),"application/json");
          return ;
        }
        //3.检查参数释放正确
        if(req_json["title"].empty()||req_json["content"].empty()||req_json["create_time"].empty())
        {
          //构造错误信息返回给客户端
          resp_json["ok"]=false;
          resp_json["reason"]="更新博客失败";
          resp.status=400;
          resp.set_content(writer.write(resp_json),"application/json");
          return ;
        }
        req_json["blog_id"]=blog_id;//从path中获取blog_id
        //4.操作mysql
        ret=blog_table.Update(req_json);
        if(!ret)
        {
          //插入失败返回错误信息给用户
          resp_json["ok"]=false;
          resp_json["reason"]="更新博客失败！";
          resp.status=500;
          //writer 将json转为字符串
          resp.set_content(writer.write(resp_json),"application/json");
          return ;
        }
        //5.构造正确返回结果 
        resp_json["ok"]=true;
        resp.set_content(writer.write(resp_json),"application/json");
        return  ;
    });
    
    //删除
    server.Delete(R"(/blog/(\d+))",[&blog_table](const Request& req,Response& resp){
        Json::FastWriter writer;
        //1.获取blog_id
        int32_t blog_id=std::stoi(req.matches[1].str());
        printf("删除id为%d的博客!\n",blog_id);
        //2.调用数据库
        Json::Value resp_json;
        bool ret=blog_table.Delete(blog_id);
        if(!ret)
        {
          printf("执行删除失败!\n");
          resp_json["ok"]=false;
          resp_json["reason"]="delete blog failed";
          resp.status=500;
          resp.set_content(writer.write(resp_json),"application/json");
          return ;
        }
        //3.构造一个正确响应
        resp_json["ok"]=true;
        resp.set_content(writer.write(resp_json),"application/json");
        return ;
        
    });

    //新增标签
    server.Post("/tag",[&tag_tabel](const Request& req,Response& resp){
        Json::FastWriter writer;
        Json::Reader reader;
        Json::Value req_json;
        Json::Value resp_json;
        //1.解析请求
        bool ret=reader.parse(req.body,req_json);
        if(!ret)
        {
          printf("插入标签失败!\n");
          resp_json["ok"]=false;
          resp_json["reason"]="Insert tag req parse failed";
          resp.status=400;
          resp.set_content(writer.write(resp_json),"application/json");
        }
        //2.对请求进行校验
        if(req_json.empty())
        {
          printf("插入标签失败!\n");;
          resp_json["ok"]=false;
          resp_json["reason"]="Insert tag req parse failed";
          resp.status=400;
          resp.set_content(writer.write(resp_json),"application");
          return ;
        }
        //i3.调用数据库完成插入
        ret=tag_tabel.Insert(req_json);
        if(!ret)
        {
          resp_json["ok"]=false;
          resp_json["reason"]="insert tag database error";
          resp.status=400;
          resp.set_content(writer.write(resp_json),"application");
          return ;
        }
        //4.返回正确结果
        resp_json["ok"]=true;
        resp.set_content(writer.write(resp_json),"application/json");
        return ;
    });

    //查看所有标签
    server.Get("/tag",[&tag_tabel](const Request& req,Response& resp){
        Json::FastWriter writer;
        Json::Value resp_json;
        Json::Value req_json;
        //1.不需要解析参数，直接执行数据库的操作
        
        bool ret=tag_tabel.SelectAll(&resp_json);
        if(!ret)
        {
          printf("获取所有标签失败\n");
          resp_json["ok"]=false;
          resp_json["reason"]="get tag database error ";
          resp.status=500;
          resp.set_content(writer.write(resp_json),"application/json");
          return ;
        }
        //2.构造正确的结果
        
        resp.set_content(writer.write(resp_json),"application/json");
        return ;
    });
    //删除标签
    server.Delete(R"(/tag/(\d+))",[&tag_tabel](const Request& req,Response& resp){
        Json::FastWriter writer;
        Json::Value resp_json;
        Json::Value req_json;
        //1.解析tag_id
        int32_t tag_id=std::stoi(req.matches[1].str());
        printf("删除标签为%d\n",tag_id);
        //2.执行数据库操作
        bool ret=tag_tabel.Delete(tag_id);
        if(!ret)
        {
          printf("删除失败!\n");
          resp_json["ok"]=false;
          resp_json["reason"]="delete tag database error";
          resp.status=500;
          resp.set_content(writer.write(resp_json),"application/json");
          return ;
        }
        //3.构造正确响应
        resp_json["ok"]=true;
        resp.set_content(writer.write(resp_json),"application/json");
        return ;
    });

    
    server.set_base_dir("./wwwroot");

    //启动服务器
    server.listen("0.0.0.0",9093);

    return 0;
}
