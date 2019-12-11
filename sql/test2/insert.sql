/*insert into students(id,sn,name)values
(100,10010,'唐大师*'*/

/*insert into students(id,sn,name)values(100,10010,'唐大师')
on duplicate key update sn=10010,name='唐大师';
*/

/*替换！！
 主键或者唯一键 没有冲突，则直接插入
 主建或者唯一建 如果有冲突，则删除后直接插
入
1 row affected 表示表中没有冲突数据，数据被插入
2 row affected 表示有冲突数据，删除后重新被插入
*/

insert into exam_result (name,yuwen,shuxue,yingyu) values
('唐三藏',67,89,31),
('孙悟空',37,83,31),
('猪八戒',51,89,34),
('沙师弟',61,23,54);
