.PHONY:run-server-tcp,run-client-tcp, run-server-udp, run-client-udp
CXX=g++
CXXFLAGS=-Wall -Wpedantic -std=c++20
DEBUG_FLAG=-fdiagnostics-color=always -g

server-tcp: server-tcp.cpp
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAG) server-tcp.cpp -o server-tcp

run-server-tcp: server-tcp 
	./server-tcp 

client-tcp: client-tcp.cpp
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAG) client-tcp.cpp -o client-tcp

run-client-tcp:client-tcp
	./client-tcp

server-udp: server-udp.cpp
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAG) server-udp.cpp -o server-udp

run-server-udp: server-udp 
	./server-udp 

client-udp: client-udp.cpp
	$(CXX) $(CXXFLAGS) $(DEBUG_FLAG) client-udp.cpp -o client-udp

run-client-udp:client-udp
	./client-udp