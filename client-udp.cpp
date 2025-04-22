#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <iostream>  

#define PORT     8080 
#define MAXLINE 1024 
   
// Driver code 
int main() { 
    //creating UDP socket 
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
    if( sockfd < 0 ){ 
        std::cerr << "Socket creation failed\n"; 
        return -1; 
    } 
    
    sockaddr_in servAddress; 
    memset(&servAddress, 0, sizeof(servAddress)); 

    // Filling server information 
    servAddress.sin_family    = AF_INET; // IPv4 
    servAddress.sin_port = htons(PORT); 
    if(inet_pton(AF_INET, "127.0.0.1", &servAddress.sin_addr) <= 0){
        std::cerr << "Invalid address or address not supported\n";
        return -1;
    }
    socklen_t len = sizeof(servAddress);

    char buffer[MAXLINE]; 
    while(true){
        char tempBuffer[MAXLINE] = {0};
        std::cout << "Message to send (type \"exit\" to exit): ";  
        std::cin.getline(tempBuffer, MAXLINE);  // Get input safely 
        if (strcmp(tempBuffer, "exit") == 0) {
            break;  // Stop the loop if user types "exit"
        }
        sendto(sockfd, tempBuffer, strlen(tempBuffer), 0, (const sockaddr *) &servAddress, len);
        int bytesReceived = recvfrom(sockfd, buffer, MAXLINE-1, 0, ( struct sockaddr *)&servAddress, &len);
        if(bytesReceived < 0) {
            std::cerr << "Error receiving data: " << strerror(errno) << std::endl;
            break;
        }
        buffer[bytesReceived] = '\0'; 
        printf("Server: %s\n",buffer);
    }
    close(sockfd);
    return 0;
}