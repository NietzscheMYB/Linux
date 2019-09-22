.PHONY:all
all:e_client echo_server
e_server:echo_server.cc
    g++ $^ -o $@ -std=c++11
e_client:echo_client.cc
    g++ $^ -o $@ -std=c++11
.PHONY:clean
clean:
    rm e_client e_server