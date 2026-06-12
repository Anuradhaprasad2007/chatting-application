#include "server.h"
#include <iostream>

int main() {
    Server server;
    
    if (!server.initialize(PORT)) {
        std::cerr << "Failed to initialize server\n";
        return 1;
    }
    
    server.start();
    return 0;
}