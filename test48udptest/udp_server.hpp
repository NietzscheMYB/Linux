#pragma once
#include"udp_socket.hpp"
#include"assert.h"
//通用的udp服务器类
//1.读取请求
//2.根据请求计算响应
//3.把响应写回客户端
//其中1，3是固定套路，不管是啥常见的，代码都是一样
//2.是和业务相关，所以把2对应的代码提前写出一个回调函数
typedef void (*Handler)(const std::string& req,std::string* resq);

class UdpServer{
  public:
    UdpServer()
    {
      assert(sock_.Socket());
    }
    ~UdpServer()
    {
      sock_.Close();
    }
    bool Start(const std::string& ip,uint16_t port,Handler Handler)
    {
        //1.创建socket 已经完成
        //2.绑定端口号
        bool ret=sock_.Bind(ip,port);
        if(!ret)
        {
          return false;
        }
        //3.进入死循环
        while(1)
        {
          //处理每个请求
          //a.读取请求
          std::string req;
          std::string peer_ip;
          uint16_t peer_port;
          sock_.RecvFrom(&req,&peer_ip,&peer_port);
          //b.根据请求计算响应
          std::string resp;
          Handler(req,&resp);
          //c.把响应返回给客户端
          sock_.SendTo(resp,peer_ip,peer_port);
        }
    }
  private:
    UdpSocket sock_;
};
