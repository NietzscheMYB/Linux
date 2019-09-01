test:ku.c libadd.a
	gcc $^ -o $@
libadd.a:add.c
	gcc -c add.c -o add.o
	ar -rc libadd.a add.o

.PHONY:clean
clean:
	rm test
