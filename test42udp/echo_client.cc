#include"udp_client.hpp"

int main(int argc,char* argv[])
{
  
    UdpClient x(argv[1],9090);
    while(1)
    {
        printf("请输入：");
        fflush(stdout);
        char buf[1024]={0};
        scanf("%s",&buf);
        std::string s;
        s.assign(buf);
        x.SendTo(s);
        char outbuf[1024]={0};

        std::string s2;
        x.RecvFrom(s2);
        printf("返回值为：%s\n",s2.c_str());
    }


    return 0;
}