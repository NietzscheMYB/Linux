#include"library.hpp"

int main()
{
  MYSQL* connect_fd=MySQLInit();
  BookTable bt(connect_fd);
//  Book* value=new Book(1,"平凡的世界","路遥","人民出版社","文学类","F062.2/13","未借阅");
 // bt.Insert(value);

  bt.SelectAll();
  cout<<endl;
  string name="皮";
  bt.Find(&name);

 // bt.Delete(value);





  return 0;
}
