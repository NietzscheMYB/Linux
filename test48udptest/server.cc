#include<stdio.h>
#include<netinet/in.h>  //ipv4地址格式
#include<sys/socket.h> //网络套接字
#include<arpa/inet.h>//网络字节序相互转换
#include<string.h>
#include<unistd.h>

//先实现udp版本的服务器
int main()
{
    //1.先创建一个socket
    //AF_INET 是一个宏，表示用ipv4协议  AF_INET6 ipv6
    //SOCK_DGRAM 表示使用UDP协议
    //第三个参数一般为0
    int sock=socket(AF_INET,SOCK_DGRAM,0);
    if(sock<0)
    {
        //打开失败
        perror("socket");
        return 1;
    }
    //2.把当前的socket绑定上一个ip+端口号
    sockaddr_in addr;
    addr.sin_family=AF_INET;//使用那个协议家族
    //ip地址也是一个整数，也需要转换成网络字节序
    //只不过inet_addr函数自动帮我们转成网络字节序
    addr.sin_addr.s_addr=inet_addr("0.0.0.0");
    //端口号必须先转成网络字节序
    //9090是主机字节序
    addr.sin_port=htons(9090);//主机序转网络序，s是短整形

    //第三个参数是addr多少个字节
    int ret=bind(sock,(sockaddr*)&addr,sizeof(addr));
    if(ret<0)
    {
        perror("bind");
        return 1;
    }
    printf("server start ok!\n");

    //3.处理服务器收到的请求
    while(true)
    {
        //a.读取客户端请求
        //面向数据报的函数接口
        sockaddr_in peer;//对端信息，输入型参数，不需要手动初始化
        //len 输入输出型参数 由于不知道对方是什么协议，显示告诉你有多长
        socklen_t len=sizeof(peer);
        char buf[1024]={0};//想象成缓冲区，从网卡读
        //recvfrom面向数据报对应udp
        //第三个sizeof(buf)-1 ,做人留一线
        ssize_t n=recvfrom(sock,buf,sizeof(buf)-1,0,(sockaddr*)&peer,&len);
        //5 6参数是客户端的ip地址与端口号
        if(n<0)
        {
            perror("recvfrom");
            continue;//考虑到容错，不要因一次请求失败
        }
        buf[n]='\0';
        //inet_ntoa 字符串转为点份10进制！！！
        printf("[%s:%d]buf:%s\n",inet_ntoa(peer.sin_addr),ntohs(peer.sin_port),buf);//网络序port转为主机字节序
        //b.根据请求计算相应
        //[略]此处写的是一个回显服务器(echo server);
        //c.把响应写回客户端
        //sendto写回客户端
        n=sendto(sock,buf,strlen(buf),0,(sockaddr*)&peer,len); 
        if(n<0)
        {
            perror("sendto");
            return 1;
        }

    }
    close(sock);
    return 0;
}