cmake_minimum_required(VERSION 3.10)
project(ChatApplication)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src)

# Server executable
add_executable(ChatApp_Server
    src/server/server.cpp
    src/server/main.cpp
)

# Client executable
add_executable(ChatApp_Client
    src/client/client.cpp
    src/client/main.cpp
)

# Link libraries
if(WIN32)
    target_link_libraries(ChatApp_Server ws2_32)
    target_link_libraries(ChatApp_Client ws2_32)
else()
    target_link_libraries(ChatApp_Server pthread)
    target_link_libraries(ChatApp_Client pthread)
endif()