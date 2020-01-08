#include"library.hpp"

void menu()
{
    cout<<"=========================================="<<endl;
    cout<<"=============欢迎管理员！=================="<<endl;
    cout<<"=========================================="<<endl;
    cout<<"======1.新增图书=======2.查看所有图书======="<<endl;
    cout<<"======3.查找图书=======4.更新图书=========="<<endl;
    cout<<"======5.删除图书=======6.图书排序=========="<<endl;
    cout<<"=========================================="<<endl;
}

void fun1(BookTable& bt)
{
    Book value;
    cout<<"请输入编号,书名,作者,出版社,类型,位置"<<endl;
    cin>>value._id>>value._name>>value._author>>value._press>>value._type>>value._location;
    bt.Insert(&value);
    
}

void fun2(BookTable& bt)
{
    bt.SelectAll();    
}
void fun3(BookTable&bt)
{
    cout<<"请输入书名"<<endl;
    string name;
    cin>>name;
    bt.Find(&name);    
}
void fun4(BookTable& bt)
{
    cout<<"请输入要更新书的编号"<<endl;
    int id;
    cin>>id;
    cout<<"请输入要更新的书名,作者,出版社,类型,位置"<<endl;
    Book value;
    cin>>value._name>>value._author>>value._press>>value._type>>value._location;  
    bt.Update(&value);
}

void fun5(BookTable& bt)
{
    cout<<"请输入要删除的书的id与书名"<<endl;
    Book value;
    cin>>value._id>>value._name;
    bt.Delete(&value);    
}
void fun6(BookTable& bt)
{
    cout<<"排序结果如下"<<endl;
    bt.Sort();
}

int main()
{
    
    MYSQL* connected_fd=MySQLInit();
    BookTable bt(connected_fd);
    int flag=0;
    while(1)
    {
        menu();
        cin>>flag;
        switch (flag)
        {
        case 1:fun1(bt);break;
        case 2:fun2(bt);break;
        case 3:fun3(bt);break;
        case 4:fun4(bt);break;
        case 5:fun5(bt);break;
        case 6:fun6(bt);break;
        default:cout<<"输入错误!请重新输入!"<<endl;
            break;
        }
    }
}