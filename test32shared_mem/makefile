.PHONY:all
all:test test1
test:shm.c
	gcc $^ -o $@

test1:read.c
	gcc $^ -o $@
.PHONY:clean

clean:
	rm test
