#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include "server.h"
#include <iostream>
#include <cstring>

#ifdef _WIN32
    #define ERROR_MSG WSAGetLastError()
#else
    #define ERROR_MSG errno
#endif

Server::Server() : serverSocket(INVALID_SOCKET), running(false) {
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
}

Server::~Server() {
    stop();
#ifdef _WIN32
    WSACleanup();
#endif
}

bool Server::initialize(int port) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket\n";
        return false;
    }
    
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);
    
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error binding socket\n";
        return false;
    }
    
    if (listen(serverSocket, 5) == SOCKET_ERROR) {
        std::cerr << "Error listening\n";
        return false;
    }
    
    logger.logAction("Server initialized on port " + std::to_string(port));
    return true;
}

void Server::start() {
    running = true;
    std::cout << "NeuroChat Server started. Waiting for clients...\n";
    logger.logAction("Server started");
    
    while (running) {
        sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        
        SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket == INVALID_SOCKET) {
            if (running) {
                std::cerr << "Error accepting client\n";
            }
            continue;
        }
        
        std::thread clientThread(&Server::handleClient, this, clientSocket);
        clientThread.detach();
    }
}

void Server::handleClient(SOCKET clientSocket) {
    Message msg;
    std::string clientName;
    
    while (running) {
        int recvResult = recv(clientSocket, (char*)&msg, sizeof(Message), 0);
        if (recvResult <= 0) {
            break; // Client disconnected
        }
        
        switch (msg.type) {
            case MSG_LOGIN:
                handleLogin(clientSocket, msg);
                clientName = msg.senderName;
                break;
            case MSG_CHAT:
                handleChat(clientSocket, msg);
                break;
            case MSG_LOGOUT:
                handleLogout(clientSocket);
                running = false;
                break;
        }
    }
    
    if (!clientName.empty()) {
        std::lock_guard<std::mutex> lock(clientsMutex);
        connectedClients.erase(clientSocket);
        logger.logAction(clientName + " disconnected");
    }
    
    closesocket(clientSocket);
}

void Server::handleLogin(SOCKET clientSocket, const Message& msg) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    connectedClients[clientSocket] = msg.senderName;
    logger.logAction(std::string(msg.senderName) + " connected");
    
    std::cout << "[LOGIN] " << msg.senderName << " joined the chat\n";
}

void Server::handleChat(SOCKET clientSocket, const Message& msg) {
    logger.log(msg.senderName, msg.content);
    broadcastMessage(msg, clientSocket);
    
    std::cout << "[CHAT] " << msg.senderName << ": " << msg.content << "\n";
}

void Server::handleLogout(SOCKET clientSocket) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    auto it = connectedClients.find(clientSocket);
    if (it != connectedClients.end()) {
        logger.logAction(it->second + " disconnected");
        std::cout << "[LOGOUT] " << it->second << " left the chat\n";
        connectedClients.erase(it);
    }
}

void Server::broadcastMessage(const Message& msg, SOCKET senderSocket) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    for (auto& [socket, name] : connectedClients) {
        if (socket != senderSocket) {
            send(socket, (char*)&msg, sizeof(Message), 0);
        }
    }
}

void Server::stop() {
    running = false;
    if (serverSocket != INVALID_SOCKET) {
        closesocket(serverSocket);
        serverSocket = INVALID_SOCKET;
    }
}
