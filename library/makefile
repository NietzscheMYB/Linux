FLAG=-std=c++11 -L/usr/lib64/mysql -lmysqlclient

.PHONY:all
all:library_test student_test teacher_test root_test

library_test:library.hpp library.cc
	g++  library.cc -o library_test $(FLAG) 
student_test:student.cc student.hpp  show.hpp
	g++ student.cc -o student_test  $(FLAG)
teacher_test:teacher.cc teacher.hpp  teachershow.hpp
	g++ teacher.cc -o teacher_test  $(FLAG)
root_test:root.cc library.hpp 
	g++ root.cc -o root_test $(FLAG)
.PHONY:clean
clean:
	rm library_test student_test teacher_test root_test
