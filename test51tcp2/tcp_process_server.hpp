#pragma once
#include<functional>
#include<sys/wait.h>
#include"tcp_socket.hpp"
#include<signal.h>

typedef std::function<void(const std::string&,std::string* )>Handler;
#define CHECK_RET(exp) if(!(exp)){return false;}

class TcpProcessServer{
public:
   TcpProcessServer()
   {}
   ~TcpProcessServer()
   {
       listen_sock_.Close();
   } 
   bool Start(const std::string& ip,uint16_t port,Handler handler)
   {
       signal(SIGCLD,SIG_IGN);//防止出现僵尸进程
        //1.创建socket
        CHECK_RET(listen_sock_.Socket());
        //2.绑定端口号
        CHECK_RET(listen_sock_.Bind(ip,port));
        //3.监听
        CHECK_RET(listen_sock_.Listen());
        //4.进入主循环
        while(true)
        {
            //5.调用accept
            TcpSocket client_sock;
            std::string peer_ip;
            uint16_t peer_port;
            bool ret=listen_sock_.Accept(&client_sock,&peer_ip,&peer_port);
            if(!ret)
            {
                continue;
            }
            printf("[%s:%d]客户端建立连接!\n",peer_ip.c_str(),peer_port);
            //6.创建子进程，让子进程处理客户端的请求
            //父进程继续调用accept
            ProcessConnect(client_sock,handler,peer_ip,peer_port);
        }
   }
private:
    void ProcessConnect(TcpSocket& client_sock,Handler handler,const std::string&ip,uint16_t port)
    {
        //1.创建子进程
        pid_t ret=fork();
        //2.父进程直接结束这个函数
        if(ret>0)
        {
            //father
            //父进程也需要关闭这个socket
            //否则会出现文件描述符泄漏
            client_sock.Close();
            return ;
        }
        //3.子进程循环做以下事情
        //child
        while(true)
        {
            std::string req;
            int r=client_sock.Recv(&req);
            if(r<0)
            {
                //小于0 出错
                continue;
            }
            if(r==0)
            {
                printf("[%s:%d]客户端断开连接!\n",ip.c_str(),port);
                break;
            }
            printf("[%s:%d]客户端发送了%s\n",ip.c_str(),port,req.c_str());
            //b.根据请求计算响应
            std::string resp;
            handler(req,&resp);
            //c.把响应写回客户端
            client_sock.Send(resp);
        }
        //子进程的收尾工作
        //1.关闭socket
        client_sock.Close();
        //2.结束进程
        exit(0);
    }
    TcpSocket listen_sock_;
};