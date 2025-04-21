#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

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
    bind(serverSocket, (struct sockaddr*)&serverAddress,sizeof(serverAddress));

    // listening to the assigned socket
    listen(serverSocket, 5);

    // accepting connection request

    cout << "Waiting for client connection...\n";
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    cout << "Connection established!\n";

    // recieving data
    char buffer[1024] = { 0 };
    while(true){
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer)-1, 0);
        // Check for client disconnection or error
        if (bytesReceived <= 0) {
            cout << "Client disconnected or error occurred.\n";
            break;
        }

        // Ensure buffer is null-terminated for safe output
        buffer[bytesReceived] = '\0';
        
        // Print received message
        cout << "Message from client: " << buffer << endl;
    }
    // closing the socket.
    close(serverSocket);

    return 0;
}