#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

const int PORT = 8000;
const int BUFFER_SIZE = 1024;

int main()
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create server socket" << std::endl;
        return 1;
    }

    sockaddr_in serverAddress;{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        std::cerr << "Failed to bind server socket" << std::endl;
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Failed to listen on server socket" << std::endl;
        close(serverSocket);
        return 1;
    }

    std::cout << "Server is running on port " << PORT << std::endl;

    while (true) {
        sockaddr_in clientAddress;{};
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressLength);
        if (clientSocket == -1) {
            std::cerr << "Failed to accept client connection" << std::endl;
            continue;
        }

        char buffer[BUFFER_SIZE];
        std::cout << "Client connected: " << inet_ntoa(clientAddress.sin_addr) << std::endl;

        ssize_t bytesRead;
        while ((bytesRead = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
            buffer[bytesRead] = '\0';
            std::cout << "Received: " << buffer;
            send(clientSocket, buffer, bytesRead, 0);
        }

        if (bytesRead == -1) {
            std::cerr << "Failed to receive data from client" << std::endl;
        }

        close(clientSocket);
        std::cout << "Client disconnected" << std::endl;
    }

    close(serverSocket);

    return 0;
}
