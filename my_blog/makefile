.PHONY:all
all:insert select

insert:insert.cc
	g++ $^ -o $@  -lmysqlclient -L/usr/lib64/mysql
select:select.cc
	g++ $^ -o $@  -lmysqlclient -L/usr/lib64/mysql

rm:clean
clean:
	rm insert select