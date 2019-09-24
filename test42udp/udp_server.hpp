#pragma once
#include"udp_socket.hpp"
#include<cassert>
#include<functional>

//通用型udp服务器
//1.读取请求
//2.根据请求计算响应
//3.将响应写回客户端

//其中1，3是固定套路，不管啥场景，代码都一样
//2.是和业务相关，把2 的代码提取成一个回调函数


//c++11 增添函数指针与仿函数

typedef std::function<void(const std::string&,std::string*)> Handler;

class UdpServer
{
public:
    UdpServer()
    {
        //创建socket
        assert(socket_.Socket());
    }
    ~UdpServer()
    {
        socket_.Close();
    }
    //直接写一个开启，给ip与端口号，还有仿函数
    bool Start(const std::string& ip,uint16_t port,Handler handler)
    {
        bool ret=socket_.Bind(ip,port);
        if(!ret)
        {
            return false;
        }
        printf("Server start OK!\n");
        //死循环，读取请求
        while (true)
        {
            //1.读取请求，读取的是对端的请求！！！
            std::string req;
            std::string peer_ip;
            uint16_t peer_port;
            socket_.Recv(&req,&peer_ip,&peer_port);

            //2.根据请求计算响应
            std::string resp;
            handler(req,&resp);

            //3.将响应写回给客户端
            socket_.SendTo(resp,peer_ip,peer_port);

        }
        
        return true;
    }
private:
    UdpSocket socket_;
};