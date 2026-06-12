#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <cstring>

#define MAX_MESSAGE_SIZE 1024
#define MAX_NAME_SIZE 50
#define PORT 8888

// Message types
enum MessageType {
    MSG_LOGIN = 1,
    MSG_CHAT = 2,
    MSG_LOGOUT = 3,
    MSG_SERVER_NOTIFICATION = 4
};

struct Message {
    MessageType type;
    char senderName[MAX_NAME_SIZE];
    char content[MAX_MESSAGE_SIZE];
    long timestamp;
};

#endif
