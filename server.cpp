#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <vector>

std::vector<int> clientSockets;

void handleClient(int clientSocket) {
    // Handle client communication
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived < 0) {
            std::cerr << "Error receiving message from client\n";
            break;
        } else if (bytesReceived == 0) {
            std::cout << "Client disconnected\n";
            break;
        }

        // Broadcast the message to all clients except the sender
        for (int socket : clientSockets) {
            if (socket != clientSocket) {
                send(socket, buffer, bytesReceived, 0);
            }
        }
    }

    // Close client socket
    close(clientSocket);
}

int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Error creating socket\n";
        return -1;
    }

    // Bind the socket to an IP address and port
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Error binding socket\n";
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Error listening for connections\n";
        return -1;
    }

    std::cout << "Server is listening for connections on port 8080\n";

    // Accept incoming connections and handle clients
    while (true) {
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);
        if (clientSocket < 0) {
            std::cerr << "Error accepting connection\n";
            continue;
        }

        std::cout << "New client connected\n";

        // Add client socket to the vector
        clientSockets.push_back(clientSocket);

        // Create a new thread to handle the client
        std::thread clientThread(handleClient, clientSocket);
        clientThread.detach();
    }

    // Close server socket
    close(serverSocket);

    return 0;
}