//#include "tcp_server.hpp"
//#include "tcp_process_server.hpp"
//#include "tcp_thread_server.hpp"
//#include"tcp_select_server.hpp"
#include<unordered_map>

#include"tcp_epoll_server.hpp"

std::unordered_map<std::string,std::string> dict;
void Find(const std::string& req,std::string* resp)
{
    auto it=dict.find(req);
        if(it==dict.end())
        {
            *resp="未找到";
        }else
        {
            *resp=it->second;
        }
}


int main()
{
    dict.insert(std::make_pair("hello","你好"));
    dict.insert(std::make_pair("world","世界"));
    dict.insert(std::make_pair("bit","比特"));

    //TcpServer server;
    //TcpProcessServer server;
    //TcpThreadServer server;
    //TcpSelectServer server;
    
    TcpEpollServer server;
    #if 0
    server.Start("0.0.0.0",9090,[&dict](const std::string&req, std::string*resp)
    {
        auto it=dict.find(req);
        if(it==dict.end())
        {
            *resp="未找到";
        }else
        {
            *resp=it->second;
        }
        
    });
    #endif

    server.Start("0.0.0.0",9090,Find);

    return 0;
}