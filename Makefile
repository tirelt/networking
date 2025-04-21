.PHONY:run-server-tcp,run-client-tcp, run-server-udp, run-client-udp

server-tcp: server-tcp.cpp
	g++ server-tcp.cpp -o server-tcp

run-server-tcp: server-tcp 
	./server-tcp 

client-tcp: client-tcp.cpp
	g++ client-tcp.cpp -o client-tcp

run-client-tcp:client-tcp
	./client-tcp

server-udp: server-udp.cpp
	g++ server-udp.cpp -o server-udp

run-server-udp: server-udp 
	./server-udp 

client-udp: client-udp.cpp
	g++ client-udp.cpp -o client-udp

run-client-udp:client-udp
	./client-udp