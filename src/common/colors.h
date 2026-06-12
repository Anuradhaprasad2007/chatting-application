#ifndef COLORS_H
#define COLORS_H

#include <iostream>
#include <string>

#ifdef _WIN32
    #include <windows.h>
    
    class Console {
    public:
        enum Color {
            RED = 12,
            YELLOW = 14,
            GREEN = 10,
            CYAN = 11,
            BLUE = 9,
            MAGENTA = 13,
            WHITE = 7
        };
        
        static void setColor(Color c) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, c);
        }
        
        static void reset() {
            setColor(WHITE);
        }
    };
#else
    class Console {
    public:
        enum Color {
            RED = 31,
            YELLOW = 33,
            GREEN = 32,
            CYAN = 36,
            BLUE = 34,
            MAGENTA = 35,
            WHITE = 37
        };
        
        static void setColor(Color c) {
            std::cout << "\033[" << c << "m";
        }
        
        static void reset() {
            std::cout << "\033[0m";
        }
    };
#endif

#endif