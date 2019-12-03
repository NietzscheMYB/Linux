#include"udp_client.hpp"

int main(int argc,char* argv[])
{
  (void)argc;
  UdpClient client(argv[1],9090);
  while(1)
  {
    char buf[1024]={0};
    printf("请输入一段内容：");
    fflush(stdout);
    scanf("%s",buf);
    client.SendTo(buf);
    std::string buf_out;
    client.RecvFrom(&buf_out);
    printf("返回内容:%s",buf_out.c_str());
   
  }


  return 0;
}
