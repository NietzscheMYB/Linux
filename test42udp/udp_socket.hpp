#pragma once
#include<sys/socket.h>
#include<cstdio>
#include<cstring>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string>

class UdpSocket
{
public:
    UdpSocket()
    {
        fd_=-1;
    }
    bool Socket()
    {
        fd_=socket(AF_INET,SOCK_DGRAM,0);
        if(fd_<0)
        {
            perror("socket");
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
    //服务器绑定，客户端一般不用绑定
    bool Bind(const std::string& ip,uint16_t port)
    {
        //根据参数 构造一个socketadd_in
        sockaddr_in addr;
        addr.sin_family=AF_INET;
        addr.sin_port=htons(port);
        addr.sin_addr.s_addr=inet_addr(ip.c_str());

        int ret=bind(fd_,(sockaddr*)&addr,sizeof(addr));
        if(ret<0)
        {
            perror("bind");
            return false;
        }
        return true;
    }


    //接收数据，要有个字符串接收，从那接收 要有ip和端口号
    //客户端，可以不要关注服务器的ip与端口号
    bool Recv(std::string* msg, std::string* ip=NULL,uint16_t* port=NULL)
    {
        char buf[1024]={0};
        sockaddr_in peer; //输出型参数
        socklen_t len=sizeof(peer);//输入输出型参数 
        //recv就改变了peer和len
        ssize_t n=recvfrom(fd_,buf,sizeof(buf)-1,0,(sockaddr*)&peer,&len);
        if(n<0)
        {
            perror("Recv");
            return false;
        }
        msg->assign(buf);
        if(ip!=NULL)
        {
            *ip=inet_ntoa(peer.sin_addr);
        }
        if(port!=NULL)
        {
            *port=ntohs(peer.sin_port);
        }
        return true;
    }
    bool SendTo(const std::string& msg,const std::string& ip,uint16_t port)
    {
        sockaddr_in addr;
        addr.sin_family=AF_INET;
        addr.sin_port=htons(port);
        addr.sin_addr.s_addr=inet_addr(ip.c_str());
        ssize_t n=sendto(fd_,msg.c_str(),sizeof(msg),0,(sockaddr*)&addr,sizeof(addr));
        if(n<0)
        {
            perror("sento");
            return false;
        }
        return true;
    }
private:
    int fd_;//socket 文件描述符，本质是数组下标
};