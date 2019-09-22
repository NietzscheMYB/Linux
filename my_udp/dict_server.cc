//创建一个中英文翻译的服务器
//用户输入一个英文单词，返回一个翻译出来的中午结果

#include<unordered_map> //通过哈希表来实现
#include"udp_server.hpp"
using namespace std;
//1.啥样的对象才能放到vector里？
//
int main()
{
    std::unordered_map<std::string,std::string> dict;
    dict.insert(std::make_pair("hello","你好"));
    dict.insert(std::make_pair("world","世界"));
    dict.insert(std::make_pair("bit","比特"));

    UdpServer server;
    //lambda 表达式[]中可以写东西，把lambda外部的变量“捕获”到lambda表达式里面
    //不写& 就是传值，更科学是传引用
    //捕获可以按指捕获，也可以按引用捕获
    server.Start("0.0.0.0",9090,[&dict](const std::string& req,std::string* resp)
    {
        //不用auto 就会写一长串 的迭代器类型
        auto it=dict.find(req);
        if(it==dict.end())
        {
            *resp="未找到结果";
        }else
        {
            *resp=it->second;//first 英文  second 中文
        }
    });
}