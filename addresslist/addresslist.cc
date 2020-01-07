#include"addresslist.hpp"
#if 0
int main()
{
    AddressList al;
    al.Insert("小明","西安科技大学","123456","1023826776@qq.com",714009);
    al.Insert("小红","西安科技大学","123456","1023826776@qq.com",714008);

    al.Insert("小刚","西安科技大学","123456","1023826776@qq.com",714001);
    al.Print();
    al.Sort();
    cout<<endl;
    al.Print();
    return 0;
}
#endif

int main()
{
  MYSQL* mysql=MySQLInit();
  AddressTable al(mysql);
  Data* value=new Data("小红","西安科技大学","13113","012313",714111);
 // assert( al.Insert(value));
//  assert(al.SelectALL());
   al.SelectAll();

   cout<<endl<<endl;
    string s="小明";
   al.Find(&s);

cout<<endl;
//  al.Update(value);
    

    al.Sort();
   return 0;
}
