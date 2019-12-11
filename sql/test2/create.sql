create table if not exists students(
    id int unsigned primary key auto_increment,
    sn int not null unique comment'学号',
    name varchar(20) not null,
    qq varchar(20)
);

/*·
insert into students values(102,20001,'曹孟德',null),
(103,20002,'孙仲谋',null);
*/

create table exam_result(
  id int unsigned primary key auto_increment,
  name varchar(20) not null comment'同学姓名',
  yuwen float default 0.0 comment'语文成绩',
  shuxue float default 0.0 comment'数学成绩',
  yingyu float default 0.0 comment'英语'
);
