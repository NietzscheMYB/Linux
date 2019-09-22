#include"udp_client.hpp"

int main(int argc,char* argv[])
{
    UdpClient x("127.0.0.1",9090);
    while(1)
    {
        printf("请输入：");
        fflush(stdout);
        char buf[1024]={0};
        scanf("%s",&buf);
        x.SendTo(buf);
        std::string out;
        x.RecvFrom(&out);
        printf("返回为：");
        fflush(stdout);
        printf("%s",out.c_str());
    }
    return 0;
}