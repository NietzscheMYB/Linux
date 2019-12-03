.PHONY:all
all:server client

server:echo_server.cc
	g++ $^ -o $@
client:echo_client.cc
	g++ $^ -o $@

.PHONY:clean
clean:
	rm server client
