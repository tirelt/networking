#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
    // creating TCP socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // specifying the address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // binding socket.
    if( bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
        std::cerr << "Bind failed\n";
        return -1;
    }

    // listening to the assigned socket
    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Listen failed\n";
        return -1;
    }

    // accepting connection request

    std::cout << "Waiting for client connection...\n";
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    std::cout << "Connection established!\n";

    // recieving data
    char buffer[1024] = { 0 };
    while(true){
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer)-1, 0);
        // Check for client disconnection or error
        if (bytesReceived <= 0) {
            std::cout << "Client disconnected or error occurred.\n";
            break;
        }

        // Ensure buffer is null-terminated for safe output
        buffer[bytesReceived] = '\0';
        
        // Print received message
        std::cout << "Message from client: " << buffer << std::endl;
    }
    // closing the socket.
    close(serverSocket);

    return 0;
}