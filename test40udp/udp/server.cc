#include<cstdio>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<cstring>
//先实现udp版本的服务器

int main()
{
    //1.先创建一个socket
    //AF_INET 是一个宏，表示使用ipv4协议
    //AF_INET6 是ipv6协议
    //SOCK_DGRAM 表示使用udp协议
    //第三个参数一般为0
    int sock=socket(AF_INET,SOCK_DGRAM,0);
    if(sock<0)
    {
        //打开失败
        perror("socket");
        return 1;
    }

    //2.把当前的socket绑定一个ip+端口号
    sockaddr_in addr;
    addr.sin_family=AF_INET;//使用哪个协议家族
    //ip---32位  42亿9千万
    addr.sin_addr.s_addr=inet_addr("0.0.0.0");//inet_addr函数自动将ip地址（32）位，转为网络字节序
    addr.sin_port=htons(9090);//主机序转为网络序，s是短整型  16位端口号！！
    //sockaddr_in 必须强转成sockaddr 因为当时socket比较老，为了通用性
    int ret=bind(sock,(sockaddr*)&addr,sizeof(addr));
    if(ret<0)
    {
        perror("bind");
        return 1;
    }
    //bind成功，即“信号良好可以接受电话”
    printf("server start ok!\n");
    
    //3.处理服务器收到的请求
    while(true)
    {
        //a.读取客户端请求
        //面向数据报的函数接口
        sockaddr_in peer;//对端（客户端）信息输入型参数，不需要手动初始化
        //读长度，才能知道具体是什么协议
        socklen_t len=sizeof(peer);//输入输出参数
        char buf[1024]={0};//想象成缓冲区，从网卡读
        ssize_t n=recvfrom(sock,buf,sizeof(buf)-1,0,(sockaddr*)&peer,&len);//5 6参数是客户端的ip端口
        if(n<0)
        {
            perror("recvfrom");
            continue;//考虑到容错，不要因一次请求失败
        }
        buf[n]='\0';
        printf("[%s:%d]buf:%s\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port),buf);
        //b.根据请求计算响应
        //[略]此处写的是一个回显服务器（echo server）；
        //c.把响应写回客户端
        //sendto 写回客户端
        n=sendto(sock,buf,strlen(buf),0,(sockaddr*)&peer,len);//第五个参数将信息发送给客户端
        if(n<0)
        {
            perror("sendto");
            return 1;
        }

    }
    close(sock);
    return 0;
}
