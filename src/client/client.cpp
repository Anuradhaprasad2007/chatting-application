#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include "client.h"
#include "../common/colors.h"
#include <iostream>
#include <cstring>

Client::Client() : socket(INVALID_SOCKET), connected(false) {
#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
}

Client::~Client() {
    disconnect();
#ifdef _WIN32
    WSACleanup();
#endif
}

bool Client::connect(const std::string& serverIP, int port) {
    socket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (socket == INVALID_SOCKET) {
        std::cerr << "Error creating socket\n";
        return false;
    }
    
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    
#ifdef _WIN32
    serverAddr.sin_addr.S_un.S_addr = inet_addr(serverIP.c_str());
#else
    inet_pton(AF_INET, serverIP.c_str(), &serverAddr.sin_addr);
#endif
    
    if (::connect(socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error connecting to server\n";
        return false;
    }
    
    connected = true;
    return true;
}

bool Client::login(const std::string& name) {
    clientName = name;
    
    Message msg;
    msg.type = MSG_LOGIN;
    strncpy(msg.senderName, name.c_str(), MAX_NAME_SIZE - 1);
    msg.senderName[MAX_NAME_SIZE - 1] = '\0';
    strncpy(msg.content, "", MAX_MESSAGE_SIZE - 1);
    msg.content[MAX_MESSAGE_SIZE - 1] = '\0';
    
    if (send(socket, (char*)&msg, sizeof(Message), 0) == SOCKET_ERROR) {
        std::cerr << "Error sending login message\n";
        return false;
    }
    
    Console::setColor(Console::GREEN);
    std::cout << "✓ Logged in as: " << name << "\n";
    Console::reset();
    
    return true;
}

void Client::run() {
    std::thread receiveThread(&Client::receiveMessages, this);
    receiveThread.detach();
    
    std::string input;
    while (connected) {
        Console::setColor(Console::MAGENTA);
        std::cout << clientName << " > ";
        Console::reset();
        
        std::getline(std::cin, input);
        
        if (input == "exit" || input == "quit") {
            disconnect();
            break;
        }
        
        if (!input.empty()) {
            sendMessage(input);
        }
    }
}

void Client::sendMessage(const std::string& message) {
    Message msg;
    msg.type = MSG_CHAT;
    strncpy(msg.senderName, clientName.c_str(), MAX_NAME_SIZE - 1);
    msg.senderName[MAX_NAME_SIZE - 1] = '\0';
    strncpy(msg.content, message.c_str(), MAX_MESSAGE_SIZE - 1);
    msg.content[MAX_MESSAGE_SIZE - 1] = '\0';
    
    if (send(socket, (char*)&msg, sizeof(Message), 0) == SOCKET_ERROR) {
        std::cerr << "Error sending message\n";
        connected = false;
    }
}

void Client::receiveMessages() {
    Message msg;
    while (connected) {
        int recvResult = recv(socket, (char*)&msg, sizeof(Message), 0);
        if (recvResult <= 0) {
            break;
        }
        
        if (msg.type == MSG_CHAT) {
            Console::setColor(Console::CYAN);
            std::cout << "\n" << msg.senderName << ": " << msg.content << "\n";
            Console::reset();
            
            Console::setColor(Console::MAGENTA);
            std::cout << clientName << " > ";
            Console::reset();
        }
    }
}

void Client::disconnect() {
    if (connected) {
        Message msg;
        msg.type = MSG_LOGOUT;
        strncpy(msg.senderName, clientName.c_str(), MAX_NAME_SIZE - 1);
        msg.senderName[MAX_NAME_SIZE - 1] = '\0';
        send(socket, (char*)&msg, sizeof(Message), 0);
        
        connected = false;
    }
    
    if (socket != INVALID_SOCKET) {
        closesocket(socket);
        socket = INVALID_SOCKET;
    }
}
