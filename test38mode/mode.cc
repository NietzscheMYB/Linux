#include<iostream>
#include<mutex>
#include<thread>
using namespace std;
#if 0
//饿汉模式
//优点：简单
//缺点：可能会导致进程启动慢，且如果有多个单例
class Singleton{
public:
  static Singleton* GetInstance()
  {
    return &m_instance;
  }
private:
  //构造函数私有
  Singleton(){};

  //c++98防拷贝
  Singleton(Singleton const&);
  Singleton& operator=(Singleton const&);

 // Singleton(Singleton const&)=delete;
 // Singleton& operator(Singleton const&)=delete;
  static Singleton m_instance;
};
Singleton Singleton::m_instance;//在程序入口之前就完成单例对象的初始化
//因为静态变量在程序一启动时，就进行初始化
#endif


#if 0
class Single{
  public:
   static  int* GETinstance()//提供一个全局访问点，静态函数可以在类外进行访问！！！！！
    {
      return &m_instance;
    }
  private:
    Single()
    {}//构造函数私有 单例模式中只有一个实例
    Single(const Single&);
    Single& operator=(Single const&);

    //Single(const Single&)=delete;
    //Single& operator=(Single const&)=delete;
    static int m_instance;//饿汉模式，在程序一创建就有
};
int  Single::m_instance;


int main()
{
  int* p=Single::GETinstance();
  cout<<*p<<endl;
  return 0;
}
#endif


class Singleton{
  public:
    static Singleton* GetInstance()//提供一个全局访问点，static支持类外访问
    {
      if(nullptr==m_pInstance)
      {

      
         m_mtx.lock();
         if(nullptr==m_pInstance)
         {
           m_pInstance=new Singleton();
         }
         m_mtx.unlock();
      } 
    }
    //实现一个内嵌垃圾回收类
    class CGarbo
    {
      public:
        ~CGarbo()
        {
          if(Singleton::m_pInstance)
          {
            delete Singleton::m_pInstance;
          }
        }
    }
    //定义一个静态成员变量，程序结束时，系统自动调用它的析构函数从而释放单例对象
    //因为静态变量的生命周期随整个程序
    static CGarbo x;
  private:
    //构造函数私有
    Singleton()
    {}
    //防拷贝
    Singleton(const Singleton&);
    Singleton& operator=(Singleton&);

    static Singleton* m_pInstance;//单例对象指针
    static mutex m_mtx;//互斥锁
}

Singleton* Singleton::m_pInstance=nullptr;
mutex Singleton::m_mtx;
Singleton::CGarbo::x;





