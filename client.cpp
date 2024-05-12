#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

void receiveMessages(int clientSocket) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived < 0) {
            std::cerr << "Error receiving message\n";
            break;
        } else if (bytesReceived == 0) {
            std::cout << "Server disconnected\n";
            break;
        }

        std::cout << "Message from server: " << buffer << std::endl;
    }
}

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Error creating socket\n";
        return -1;
    }

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
        std::cerr << "Invalid address\n";
        return -1;
    }

    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Connection failed\n";
        return -1;
    }

    std::cout << "Connected to server\n";

    // Start a thread to receive incoming messages
    std::thread recvThread(receiveMessages, clientSocket);

    // Send messages
    char buffer[1024];
    while (true) {
        std::string message;
        std::getline(std::cin, message);

        if (send(clientSocket, message.c_str(), message.length(), 0) != message.length()) {
            std::cerr << "Error sending message\n";
            break;
        }

        if (message == "exit") {
            break;
        }
    }

    // Close the socket
    close(clientSocket);

    return 0;
}