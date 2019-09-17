#include<iostream>
#include<mutex>
#include<thread>
using namespace std;


#if 0
//饿汉模式 程序一启动就有东西
//单例模式，一个类只有一个类对象，在程序中只有该类一个实例，并且提供一个访问它的全局访问点，为所有程序模块所共享
//优点：代码jiand
//缺点:可能会导致启动变慢
//template<class T>
class Sing{
  public:
    static Sing* GetInstance()//要提共一个全局访问点，所以要用static
    {
      return &m_instance;
    }
  private:


    //构造函数私有
    Sing(){}

    //防止拷贝
    Sing(const Sing&)=delete;
    Sing& operator=(Sing&)=delete;


    static Sing m_instance;//因为一开始就要创建，所以选static
};
Sing Sing::m_instance; 
#endif



#if 0
class Sing{
public:
  static Sing* GetInstance()
  {

    if(nullptr==m_instance)
   {
    //在这个前提下为了，当创建了一次时，其他线程不知道创建了，还是去尝试创建，此时可能会在这里发送阻塞，为了提高效率
    //在加上一个if
    mt.lock();
    //在但线程下，是安全，在多线程是不安全，多线程抢占式执行，要加锁，加锁，会一定程度下降低效率
    //需要时，才去创建，而且只创建一次
    if(m_instance==nullptr)
    {
      m_instance=new Sing();//创建调构造函数
     // return m_instance;
    }
    mt.unlock();
     }
  }
  //设置一个回收类
  class Clc{
  public:
    ~Clc()
    {
      if(Sing::m_instance)
      {
        delete Sing::m_instance;
      }
    } 
  };
  static Clc x;



private:
  //构造函数私有
  Sing() {}
  //防止拷贝
  Sing(const Sing&)=delete;
  //防止赋值
  Sing& operator=(Sing&)=delete;

 volatile  static Sing* m_instance;//懒汉模式 在需要时初始化   volatile 保持内存的可见性，告诉cup要从内存中读取值
  static mutex mt;
};
mutex Sing::mt;
volatile Sing* Sing::m_instance=nullptr;
Sing::Clc x;

#endif


#if 0
//创建一个类对象，只能在堆上创建
class Headxx{
  public:
  //在不定义对象时，类外进行访问
  //所以要用static,变成全局函数
  static Headxx* get()
  {
    return new Headxx;
  }
/*
  static  void ret()
  {
    cout<<_x<<endl;
  }*///  这样写是不对的，因为static函数没有隐藏的this指针，不能反正成员变量
  private:
    //构造函数私有化
    Headxx()
    {
      _x=1;
    }
    //拷贝构造私有
    Headxx(const Headxx&)=delete ;
    //赋值运算私有
    Headxx& operator=(Headxx&)=delete ;
    int _x;
};

int main()
{
  Headxx* p=Headxx::get();
  Headxx::ret();
  return 0;
}
#endif

//创建一个类只能在栈上进行创建
class Stackxx{
  public:
    static Stackxx get()//静态成员函数可以调非静态成员函数!!!!!
    {
      return Stackxx();
    }
  private:
    Stackxx()
    {
      cout<<"hello world"<<endl;
    }
    //因为是在栈上创建，所以要把new 屏蔽调与operator new屏蔽调
    void* operator new(size_t xx);
    void operator delete(void*);
  
};

int main()
{
  Stackxx::get();
  return 0;
}
