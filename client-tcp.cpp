#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <unistd.h>

int main()
{
    //sleep(3);
    // creating socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // specifying address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    
    if(inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0){
        std::cerr << "Invalid address or address not supported\n";
        return -1;
    }

    // sending connection request
    std::cout << "Connecting to server...\n";
    if(connect(clientSocket, (struct sockaddr*)&serverAddress,sizeof(serverAddress))<0){
        std::cerr << "Connection failed: " << strerror(errno) << std::endl;
        return -1;
    };

   
    while(true){
        char tempBuffer[1024] = {0};
        std::cout << "Message to send (type \"exit\" to exit): ";  
        std::cin.getline(tempBuffer, 1024);  // Get input safely 
        if (strcmp(tempBuffer, "exit") == 0) {
            break;  // Stop the loop if user types "exit"
        }  
        if(send(clientSocket, tempBuffer, strlen(tempBuffer), 0) < 0){
            std::cerr << "Error sending data: " << strerror(errno) << std::endl;
        }
    }
    // closing socket
    close(clientSocket);

    return 0;
}
