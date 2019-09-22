#include"udp_server.hpp"
void Echo(const std::string& req,std::string* resp)
{
    *resp=req;
}

int main()
{
    UdpServer server;
   // server.Start("0.0.0.0",9090,Echo);
   //lambda 表达式 本质是一个匿名函数，为回调函数量身打造
   //[]() -> int {} 
   server.Start("0.0.0.0",9090,[](const std::string& req,std::string* resp){*resp=req;});
    return 0;
}