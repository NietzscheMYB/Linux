FLAG=-std=c++11 -lpthread -ljsoncpp
DEPEND=tcp_server.hpp tcp_socket.hpp

.PHONY:all
all: calc_server calc_client


calc_server:calc_server.cc $(DEPEND)
	g++ calc_server.cc -o calc_server $(FLAG)
calc_client:calc_client.cc $(DEPEND)
	g++ calc_client.cc -o calc_client $(FLAG)


.PHONY:clean
clean:
	rm calc_server calc_client