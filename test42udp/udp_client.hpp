#pragma once
#include"udp_socket.hpp"
#include<cassert>

class UdpClient
{
public:
    UdpClient(std::string ip="127.0.0.1" ,uint16_t port=9090 )
    :server_ip(ip)
    ,server_port(port)
    {
        assert(socket_.Socket());
    }
    ~UdpClient()
    {
        socket_.Close();
    }
    bool RecvFrom( std::string& msg)
    {
        socket_.Recv(&msg);
        return true;
    }
    bool SendTo(std::string& msg)
    {
        socket_.SendTo(msg,server_ip,server_port);
        return true;
    }
private:
    UdpSocket socket_;
    std::string server_ip;
    uint16_t server_port;
};