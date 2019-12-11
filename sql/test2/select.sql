/*通常情况下不建议使用* 进行全列查询
 1.查询的列越多，意味着需要传输的数据量越大
 2.可能会影响到索引的使用
 
select * from exam_result;

 */

--2.指定列的顺序不需要按照定义表的顺序来

-------select id,name,yingyu from exam_result;

--3.查询字段为表达式
-------表达式不包含字段
-------select id,name,10 from exam_result;
-------表达式包含一个字段
------- select id,name,yingyu+10 from exam_result;
-------表达式中包含多个字段
------- select id,name,yingyu+yuwen+shuxue from exam_result;

--4.为查询结果指定别名
--------select id,name,yingyu+yuwen+shuxue 总分 from exam_result;

--5.结果去重
--------select distinct yingyu from exam_result;

--6.where条件
--------比较运算符 > < = <=> like(模糊匹配！)
--------逻辑运算符 and or not
--------选择英语不及格的同学
--------select name,yingyu from exam_result where yingyu <60;
--------选择出语文成绩在50,100的同学
--------使用and连接
--------select name,yuwen from exam_result where yuwen>=50 and yuwen<=100;
--------使用between and 连接
        select name,yuwen from exam_result where yuwen between 50 and 100;





