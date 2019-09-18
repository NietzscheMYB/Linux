.PHONY:all
all:mserver mclient

mserver:server.cc
	g++ $^ -o $@ -std=c++11

mclient:client.cc
	g++ $^ -o $@ -std=c++11

.PHONY:clean
clean:
	rm mclient mserver