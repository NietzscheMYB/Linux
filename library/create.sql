--
--create table BookTable (
--  id int primary key,
--  name varchar(20),
--  author varchar(20),
--  press varchar(20),
--  type varchar(20),
--  location varchar(20),
--  status varchar(20) default '未借阅'
--);

--create table StudentTable (
--  id int primary key,
--  name varchar(20),
--  class varchar(20),
--  book_id varchar(20),
--  password varchar(20)
--);
--

--create table BookBorrow(
--  bookid int ,
--  username VARCHAR(20),
--  bookname varchar(20)
--);

create table TeacherTable(
  id int,
  name varchar(20),
  college varchar(20),
  password varchar(20)
);