FLAG=-std=c++11 -L/usr/lib64/mysql -lmysqlclient

.PHONY:all
all:library_test student_test

library_test:library.hpp library.cc
	g++  library.cc -o library_test $(FLAG) 
student_test:student.cc student.hpp show.cc show.hpp
	g++ student.cc -o student_test  $(FLAG)
.PHONY:clean
clean:
	rm library_test student_test
