#ifndef LOGGER_H
#define LOGGER_H

#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

class Logger {
private:
    std::ofstream logFile;
    
public:
    Logger(const std::string& filename = "chat_log.txt") {
        logFile.open(filename, std::ios::app);
    }
    
    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }
    
    void log(const std::string& userName, const std::string& message) {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
        
        logFile << "[" << ss.str() << "] " << userName << ": " << message << "\n";
        logFile.flush();
    }
    
    void logAction(const std::string& action) {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
        
        logFile << "[" << ss.str() << "] [SYSTEM] " << action << "\n";
        logFile.flush();
    }
};

#endif
