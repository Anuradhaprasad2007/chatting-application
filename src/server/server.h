#ifndef SERVER_H
#define SERVER_H

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <map>
#include <string>
#include <thread>
#include <mutex>
#include "../common/protocol.h"
#include "../common/logger.h"

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    typedef int socklen_t;
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket close
    typedef int SOCKET;
#endif

class Server {
private:
    SOCKET serverSocket;
    std::map<SOCKET, std::string> connectedClients; // socket -> client name
    std::mutex clientsMutex;
    Logger logger;
    bool running;
    
public:
    Server();
    ~Server();
    
    bool initialize(int port = PORT);
    void start();
    void stop();
    
private:
    void handleClient(SOCKET clientSocket);
    void broadcastMessage(const Message& msg, SOCKET senderSocket);
    void handleLogin(SOCKET clientSocket, const Message& msg);
    void handleChat(SOCKET clientSocket, const Message& msg);
    void handleLogout(SOCKET clientSocket);
};

#endif
