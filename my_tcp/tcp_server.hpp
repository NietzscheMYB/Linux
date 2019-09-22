//通用的TCP服务器
#pragma once

#include<functional>
#include"tcp_socket.hpp"


#define CHECK_RET(exp) if(!(exp)) {return false;}

typedef std:: function<void (const std::string& ,std::string*)> Handler;
class TcpServer
{
public:
    TcpServer()
    {

    }
    bool Start(const std::string& ip,uint16_t port,Handler handler)
    {
        //1.创建一个socke
        CHECK_RET(listen_sock_.Socket());
       
        //2.绑定端口号
       CHECK_RET(listen_sock_.Bind(ip,port));
       
        //3.进行监听
        CHECK_RET(listen_sock_.Listen());
        printf("Server Start OK\n");
        
        //4.进入主循环
        while(true)
        {
            //5.通过accept获取连接
            TcpSocket client_sock;
            std::string ip;
            uint16_t port;

            //accept 只调用了一次！！！
            //核心问题在于，第一次accept 后就进入了一个循环
            //在这个操作过程中，循环一直没有结束，accept没有重复调用
            //后续连接过来的客户端都在内核的连接队列中排队呢，一直得不到处理
            //应该想办法让我们的程序能够更快的调用到accept！
            //多进程或者多线程

            bool ret=listen_sock_.Accept(&client_sock,&ip,&port);
            if(!ret)
            {
                  continue;  //失败 继续
            }
            printf("[%s:%d] 有客户端连接",ip.c_str(),port);
            //6.和客户端进行具体沟通。一次连接中和客户端进行多出交流
            while(true)
            {
                //a。读取请求
                std::string req;
                int r=client_sock.Recv(&req);
                if(r<0)
                {
                    continue;
                }
                if(r==0)
                {
                    //对端关闭了socket
                    client_sock.Close();            
                    //accept 获取对端ip和端口
                    printf("[%s:%d]对端关闭了连接\n",ip.c_str(),port);
                    break;
                }
                printf("[%s:%d]客户端发送了：%s\n",ip.c_str(),port,req.c_str());
                //b。根据请求计算响应
                std::string resp;
                handler(req,&resp);
                //c.把响应写回客户端
                client_sock.Send(resp);
            }
        }
    }
private:
    TcpSocket listen_sock_;//外场拉客
};