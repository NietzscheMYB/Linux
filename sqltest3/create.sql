create table if not exists temp(
  id int primary key auto_increment,
  birthday date
);

create table if not exists msg(
  id int primary key auto_increment,
  content varchar(30) not null,
  sendtime datetime
);
