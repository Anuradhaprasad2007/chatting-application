#include "client.h"
#include "../common/colors.h"
#include <iostream>

int main() {
    Console::setColor(Console::CYAN);
    std::cout << "╔════════════════════════════════════╗\n";
    std::cout << "║     NeuroChat Client v2.0          ║\n";
    std::cout << "║     Multi-Client Chat System       ║\n";
    std::cout << "╚════════════════════════════════════╝\n\n";
    Console::reset();
    
    std::string serverIP = "127.0.0.1";
    std::string clientName;
    
    std::cout << "Enter server IP (default 127.0.0.1): ";
    std::string input;
    std::getline(std::cin, input);
    if (!input.empty()) {
        serverIP = input;
    }
    
    Client client;
    if (!client.connect(serverIP, PORT)) {
        std::cerr << "Failed to connect to server\n";
        return 1;
    }
    
    Console::setColor(Console::YELLOW);
    std::cout << "Connected to server at " << serverIP << "\n";
    Console::reset();
    
    std::cout << "Enter your name: ";
    std::getline(std::cin, clientName);
    
    if (!client.login(clientName)) {
        std::cerr << "Failed to login\n";
        return 1;
    }
    
    Console::setColor(Console::GREEN);
    std::cout << "Type your messages (type 'exit' to quit)\n";
    Console::reset();
    
    client.run();
    
    return 0;
}