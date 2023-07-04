#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <poll.h>

const int PORT = 8000;
const int BUFFER_SIZE = 1024;
const int MAX_CLIENTS = 10;

int main()
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create server socket" << std::endl;
        return 1;
    }

    sockaddr_in serverAddress{};
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

    std::vector<pollfd> clientSockets;
    clientSockets.push_back({serverSocket, POLLIN, 0});

    while (true) {
        int activity = poll(clientSockets.data(), clientSockets.size(), -1);
        if (activity == -1) {
            std::cerr << "Error in polling" << std::endl;
            break;
        }

        if (clientSockets[0].revents & POLLIN) {
            sockaddr_in clientAddress{};
            socklen_t clientAddressLength = sizeof(clientAddress);
            int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressLength);
            if (clientSocket == -1) {
                std::cerr << "Failed to accept client connection" << std::endl;
                continue;
            }

            std::cout << "Client connected: " << inet_ntoa(clientAddress.sin_addr) << std::endl;

            clientSockets.push_back({clientSocket, POLLIN, 0});

            if (--activity <= 0) {
                continue;
            }
        }

        for (int i = 1; i < clientSockets.size(); ++i) {
            if (clientSockets[i].revents & POLLIN) {
                char buffer[BUFFER_SIZE];
                ssize_t bytesRead = recv(clientSockets[i].fd, buffer, BUFFER_SIZE - 1, 0);
                if (bytesRead == -1) {
                    std::cerr << "Failed to receive data from client" << std::endl;
                    close(clientSockets[i].fd);
                    clientSockets.erase(clientSockets.begin() + i);
                    continue;
                } else if (bytesRead == 0) {
                    std::cout << "Client disconnected" << std::endl;
                    close(clientSockets[i].fd);
                    clientSockets.erase(clientSockets.begin() + i);
                    continue;
                }

                buffer[bytesRead] = '\0';
                std::cout << "Received message from client: " << buffer << std::endl;

                const char* response = "Hello, client!";
                ssize_t bytesSent = send(clientSockets[i].fd, response, strlen(response), 0);
                if (bytesSent == -1) {
                    std::cerr << "Failed to send response to client" << std::endl;
                }

                if (--activity <= 0) {
                    break;
                }
            }
        }
    }

    close(serverSocket);

    return 0;
}
