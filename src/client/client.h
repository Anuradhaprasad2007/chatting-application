#ifndef CLIENT_H
#define CLIENT_H

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <thread>

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

#include "../common/protocol.h"

class Client {
private:
    SOCKET socket;
    std::string clientName;
    bool connected;
    
public:
    Client();
    ~Client();
    
    bool connect(const std::string& serverIP, int port);
    bool login(const std::string& name);
    void run();
    void sendMessage(const std::string& message);
    void disconnect();
    
private:
    void receiveMessages();
};

#endif
