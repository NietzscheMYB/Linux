#pragma once
#include<cstdio>
#include<cstring>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string>

class TcpSocket{
public:
    TcpSocket()
    {
        fd_=-1;
    }
    bool Socket()
    {
        //和udp不同的是第二个参数，面向数据流
        fd_=socket(AF_INET,SOCK_STREAM,0);
        if(fd_<0)
        {
            perror("socket");
            return false;
        }
        return true;
    }
    //给服务器使用
    bool Bind(const std::string &ip,uint16_t port)
    {
        sockaddr_in addr;
        addr.sin_family=AF_INET;
        addr.sin_addr.s_addr=inet_addr(ip.c_str());
        addr.sin_port=htons(port);
        //bind()作用是将参数socket文件描述符和myaddr绑定在一起
        //使socketfd这个用来网络通信的文件描述符监听addr所描述的地址和端口号
        int ret=bind(fd_,(sockaddr*)&addr,sizeof(addr));
        if(ret<0)
        {
            perror("bind");
            return false;
        }
        return true;
    }
    //给服务器使用
    bool Listen()
    {
        //listen声明socket处于监听状态
        //并且最多允许有backlog(listen的第二个参数)个客户端处于连接等待状态
        //如果收到更多的连接请求就会忽略

        //listen 进入监听状态
        int ret=listen(fd_,10);//连接队列的长度！！
        if(ret<0)
        {
            perror("listen");
            return false;
        }
        return true;
    }
    //给服务器用
    bool Accept(TcpSocket* peer,std::string* ip=NULL,uint16_t* port=NULL)
    {
        //accept 从连接队列中取一个连接到用户代码中
        //如果队列中没有连接，会阻塞(默认行为)
        sockaddr_in peer_addr;
        socklen_t len=sizeof(peer_addr);
        //accept 返回也是一个socket
        //后续和客户端沟通借助client_sock 内场
        int client_sock=accept(fd_,(sockaddr*)&peer_addr,&len);
        if(client_sock<0)
        {
            perror("accept");
            return false;
        }
        peer->fd_=client_sock;
        if(ip!=NULL)
        {
            *ip=inet_ntoa(peer_addr.sin_addr);
        }
        if(port!=NULL)
        {
            *port=ntohs(peer_addr.sin_port);
            //网络序转主机序
        }
        return true;

        //三次握手完成后，服务器调用accept()接收连接
        //如果服务器调用accept()时还没有客户端的连接请求，就阻塞等待直到有客户端连接上来
    }
    //给客户端和服务器使用
    int Recv(std::string* msg)
    {
        msg->clear();
        char buf[1024*10]={0};
        ssize_t n=recv(fd_,buf,sizeof(buf)-1,0);
        //recv的返回值，如果读取成功，返回结果为读到的字节数
        //读取失败，返回结果为-1
        //如果对端关闭了socket返回结果为0
        if(n<0)
        {
            perror("recv");
            return -1;
        }else if(n==0)
        {
            //需要考虑返回0的情况
            return 0;
        }
        msg->assign(buf);//赋值
        return 1;
    }
    //给客户端和服务器使用
    bool Send(const std::string& msg)
    {
        //第四个参数填0就行
        ssize_t n=send(fd_,msg.c_str(),msg.size(),0);
        if(n<0)
        {
            perror("send");
        }
        return true;
    }
    //给客户端
    bool Connect(const std::string& ip,uint16_t port)
    {
       //connect 连接服务器，进行三次握手 

        //connect是对方的地址和ip
       sockaddr_in addr;
       addr.sin_addr.s_addr=inet_addr(ip.c_str());
       addr.sin_port=htons(port);
       addr.sin_family=AF_INET;
       int ret=connect(fd_,(sockaddr*)&addr,sizeof(addr));
       if(ret<0)
       {
           perror("connect");
            return false;
       } 
       return true;
    }
    bool Close()
    {
        if(fd_!=-1)
        {
            close(fd_);
        }
        return true;
    }
private:
    int fd_;
};











