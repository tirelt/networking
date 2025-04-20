.PHONY:run-server-tcp,run-client-tcp

server-tcp: server-tcp.cpp
	g++ server-tcp.cpp -o server-tcp

run-server-tcp: server-tcp 
	./server-tcp 

client-tcp: client-tcp.cpp
	g++ client-tcp.cpp -o client-tcp

run-client-tcp:client-tcp
	./client-tcp
