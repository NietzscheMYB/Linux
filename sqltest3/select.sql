--select * from temp;
--select * from msg;
--select content,date(sendtime) from msg;
select *from msg where date_add(sendtime,interval 2 minute) > now();
