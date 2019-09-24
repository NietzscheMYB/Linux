.PHONY:all
all:echo_server echo_client
echo_client:echo_client.cc
	g++ $^ -o $@ -std=c++11 
echo_server:echo_server.cc
	g++ $^ -o $@ -std=c++11
.PHONY:clean
clean:
	rm echo_client echo_server