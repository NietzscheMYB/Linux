#include"tcp_thread_server.hpp"

void HttpProcess(const std::string&req,std::string* resp)
{
    //不管输入啥都反回hello world

    //去解析请求即可
    (void) req;
    std::string first_lin="HTTP/1.1 302 Found\n";
    std::string header="Location:http://www.sogou.com\n"
        "Content-Type:text/html\n"
        "Content-Length:10\n";         //每行写一个字符串，相当于字符串拼接
    std::string body="aaaaaaaaaa";
    

    #if 0  //200
    std::string first_lin="HTTP/1.1 200 OK\n";
    std::string body="<html><div>hello world</div></html>";
    std::string header="Content-Type: text/html\nContent-Length:"+std::to_string(body.size())+"\n";
    #endif

    *resp=first_lin+header+"\n"+body;
}


int main()
{
    TcpThreadServer server;
    server.Start("0.0.0.0",9090,HttpProcess);
    return 0;
}