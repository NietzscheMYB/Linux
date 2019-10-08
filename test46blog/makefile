.PHONY:all
all:insert

insert:insert.cc
	g++ $^ -o $@  -lmysqlclient -L/usr/lib64/mysql
rm:clean
clean:
	rm insert