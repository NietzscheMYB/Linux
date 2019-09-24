#include"tcp_thread_server.hpp"
#include<jsoncpp/json/json.h>  

//请求
//"10 20 +"
//响应
//"30"

//使用json的方式进行序列化和反序列化
//{
//  "num1":10,
//  "num2":20,
//  "op":+,
//}


//{
//    "num":[10,20,30,40],
//    "op":"+",
//}

//{
//    "result":30
//}

//如何解析Json格式？ 涉及到编译原理中的一些内容
//借助第三方库，直接完成解析和操作
//jsoncpp
//Json::Value 用来表示一个Json数据
//Json::Reader 把字符串转成Json::Value
//Json::Writer 把Json::Value 转换成字符串

int main()
{
    TcpThreadServer server;
    server.Start("0.0.0.0",9090,[](const std::string& req,std::string* resp)
    {
        //1.先将req进行反序列化
        Json::Reader reader;
        Json::Value req_json;  //核心数据被解析到req_json
        reader.parse(req,req_json);//第二个参数是输出型参数
        //2.根据反序列化的结果，进行计算

        //处理多个数！！！
       Json::Value& nums=req_json["nums"]; //nums涵盖数组
        std::string op=req_json["op"].asString();
        int result=0;
        for(size_t i=0;i<nums.size();++i)
        {
            if(op=="+")
            {
                result+=nums[(int)i].asInt();
            }else if(op=="-")
            {
                result-=nums[(int)i].asInt();
            }
        }
       
       //处理2个数！！！
       #if 0
        int num1=req_json["num1"].asInt();
        int num2=req_json["num2"].asInt();
        std::string op=req_json["op"].asString();
        int result=0;
        if(op=="+")
        {
            result=num1+num2;
        }else if(op=="-"){
            result=num1-num2;
        }
        #endif 
        //3.需要把结果再序列化会回一个字符串
        Json::FastWriter writer;
        Json::Value resp_json;
        resp_json["result"]=result;
        *resp=writer.write(resp_json);
    });
    return 0;
}