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
    
    sockaddr_in servAddress, cliAddress; 

    memset(&servAddress, 0, sizeof(servAddress)); 
    memset(&cliAddress, 0, sizeof(cliAddress)); 

    // Filling server information 
    servAddress.sin_family    = AF_INET; // IPv4 
    servAddress.sin_port = htons(PORT); 
    servAddress.sin_addr.s_addr = INADDR_ANY; 

    socklen_t len = sizeof(cliAddress);

    // Bind the socket with the server address 
    if ( bind(sockfd, (const sockaddr*)&servAddress,sizeof(servAddress)) < 0 ){ 
        std::cerr<< "Bind failed\n"; 
        return -1; 
    } 
       
    char buffer[MAXLINE]; 
    const char *ackMsg = "ack";
    
    while(true){
        int bytesReceived = recvfrom(sockfd, (char *)buffer, MAXLINE-1, 0, ( struct sockaddr *)&cliAddress, &len); 
        if(bytesReceived < 0) {
            std::cerr << "Error receiving data: " << strerror(errno) << std::endl;
            break;
        }
        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(cliAddress.sin_addr), clientIP, INET_ADDRSTRLEN);
        
        // Ensure buffer is null-terminated for safe output
        buffer[bytesReceived] = '\0'; 

        // Print received message
        printf("Client %s: %s\n",clientIP,buffer); 
        
        // Send message to client
        sendto(sockfd, ackMsg, strlen(ackMsg), 0, (const sockaddr *) &cliAddress, len);  
    }
    close(sockfd);
    return 0; 
}