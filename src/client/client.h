#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <thread>
#include "../common/protocol.h"

#ifdef _WIN32
    #include <winsock2.h>
    typedef int socklen_t;
    #define INVALID_SOCKET INVALID_SOCKET
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