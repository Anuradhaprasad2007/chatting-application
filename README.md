# Chatting Application - Multi-Client Chat System

A cross-platform C++ console application with **server-client architecture** for real-time multi-user chat.

## ✨ Features

🖥️ **Multi-Client Support** - Connect multiple clients from different laptops  
📝 **User Names** - Each client enters their name before chatting  
💬 **Real-Time Chat** - Messages broadcast to all connected clients  
📊 **Server Logging** - All conversations logged to `chat_log.txt`  
🎨 **Colored Console Output** - Cross-platform color support  
🔧 **Cross-Platform** - Windows (Visual Studio 2022, VS Code) and Linux  
⚡ **No External Dependencies** - Only standard C++ libraries + sockets  

## System Requirements

- **Windows**: Visual Studio 2022 or VS Code with MinGW
- **Linux/macOS**: GCC/Clang with pthread support
- **CMake**: 3.10 or higher (recommended for easy building)
- **C++ Standard**: C++17 or higher

## Project Structure

```
chatting-application/
├── src/
│   ├── common/
│   │   ├── colors.h          # Cross-platform color handling
│   │   ├── protocol.h        # Message protocol definitions
│   │   └── logger.h          # Server logging utility
│   ├── server/
│   │   ├── server.h
│   │   ├── server.cpp
│   │   └── main.cpp
│   ├── client/
│   │   ├── client.h
│   │   ├── client.cpp
│   │   └── main.cpp
├── CMakeLists.txt
├── README.md
└── .gitignore
```

---

# 🚀 How to Run - Step by Step

## ⚙️ Building the Project

### **Option 1: Using CMake (RECOMMENDED)**

#### **On Windows (Visual Studio 2022)**

1. **Install Prerequisites:**
   - Download and install [Visual Studio 2022](https://visualstudio.microsoft.com/vs/) with C++ development tools
   - Download and install [CMake](https://cmake.org/download/)

2. **Clone the repository:**
   ```bash
   git clone https://github.com/Anuradhaprasad2007/chatting-application.git
   cd chatting-application
   ```

3. **Create build directory and configure:**
   ```bash
   mkdir build
   cd build
   cmake -G "Visual Studio 17 2022" -A x64 ..
   ```

4. **Build the project:**
   ```bash
   cmake --build . --config Release
   ```

5. **Executables will be at:**
   ```
   build/Release/ChatApp_Server.exe
   build/Release/ChatApp_Client.exe
   ```

#### **On Linux/macOS**

1. **Install prerequisites:**
   ```bash
   # Ubuntu/Debian
   sudo apt-get install build-essential cmake
   
   # macOS (if using Homebrew)
   brew install cmake
   ```

2. **Clone and build:**
   ```bash
   git clone https://github.com/Anuradhaprasad2007/chatting-application.git
   cd chatting-application
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

3. **Executables will be at:**
   ```
   build/ChatApp_Server
   build/ChatApp_Client
   ```

---

### **Option 2: Using Visual Studio 2022 IDE**

1. Open **Visual Studio 2022**
2. Click **File → Open → Folder** (or **Clone a repository**)
3. Navigate to the `chatting-application` folder
4. Visual Studio will detect CMakeLists.txt automatically
5. Select **Build → Build All** (or press Ctrl+Shift+B)
6. Run using the dropdown in the toolbar

---

### **Option 3: Using VS Code**

1. **Install Extensions:**
   - C/C++ Extension Pack
   - CMake Tools
   - CMake

2. **Open the project:**
   ```bash
   code chatting-application
   ```

3. **Build:**
   - Press `Ctrl+Shift+B`
   - Select "CMake: build"

4. **Run from integrated terminal:**
   ```bash
   cd build
   ./ChatApp_Server    # Linux/macOS
   ChatApp_Server.exe  # Windows
   ```

---

## 📖 Running the Application

### **Step 1: Start the Server (on one machine)**

**Windows:**
```bash
cd build\Release
.\ChatApp_Server.exe
```

**Linux/macOS:**
```bash
cd build
./ChatApp_Server
```

**Expected output:**
```
╔════════════════════════════════════════╗
║                                        ║
║    NeuroChat Server - Waiting...       ║
║                                        ║
╚════════════════════════════════════════╝

NeuroChat Server started. Waiting for clients...
```

### **Step 2: Connect Clients (from multiple machines)**

**On Client Machine 1 (Windows):**
```bash
cd build\Release
.\ChatApp_Client.exe
```

**On Client Machine 2 (Windows):**
```bash
cd build\Release
.\ChatApp_Client.exe
```

**On Linux/macOS:**
```bash
cd build
./ChatApp_Client
```

---

## 💬 Usage Example

### **When Client Starts:**

```
╔════════════════════════════════════╗
║     NeuroChat Client v2.0          ║
║     Multi-Client Chat System       ║
╚════════════════════════════════════╝

Enter server IP (default 127.0.0.1): 192.168.1.100
```

💡 **To connect from another machine, enter the server's IP address**

For local testing on same machine: `127.0.0.1`

### **Enter Your Name:**

```
Connected to server at 192.168.1.100
Enter your name: Alice
✓ Logged in as: Alice
Type your messages (type 'exit' to quit)
```

### **Start Chatting:**

```
Alice > Hello everyone!

Bob: Hi Alice! How are you?

Alice > I'm great! What's up?
```

**To exit:** Type `exit` or `quit`

---

## 🌐 Connecting from Different Laptops

### **Find Your Server's IP Address:**

**Windows:**
```bash
ipconfig
# Look for "IPv4 Address" under your network adapter (e.g., 192.168.1.100)
```

**Linux/macOS:**
```bash
ifconfig
# or
ip addr
# Look for inet address (e.g., 192.168.1.100)
```

### **Firewall Setup:**

**Windows:**
- Windows Defender Firewall might block port 9999
- Go to **Windows Defender Firewall → Allow an app through firewall**
- Add ChatApp_Server.exe

**Linux:**
```bash
# Allow port 9999
sudo ufw allow 9999/tcp
```

**macOS:**
```bash
# Check if firewall is blocking
sudo /usr/libexec/ApplicationFirewall/socketfilterfw --getglobalstate
```

---

## 📊 Server Logging

All messages are automatically logged to **`chat_log.txt`** in the directory where the server runs:

```
[2025-01-12 14:23:45] [SYSTEM] Server started
[2025-01-12 14:23:50] [SYSTEM] Alice connected
[2025-01-12 14:23:55] [SYSTEM] Bob connected
[2025-01-12 14:24:00] Alice: Hello everyone!
[2025-01-12 14:24:05] Bob: Hi Alice! How are you?
[2025-01-12 14:24:10] Alice: I'm great! What's up?
[2025-01-12 14:25:00] [SYSTEM] Bob disconnected
```

---

## 🔧 Networking Details

| Parameter | Value |
|-----------|-------|
| Protocol | TCP/IP |
| Default Port | 9999 |
| Max Message Size | 1024 bytes |
| Max Name Size | 50 characters |
| Max Concurrent Clients | Limited by OS |

### **Change Port Number:**

Edit `src/common/protocol.h` line 6:
```cpp
#define PORT 9999  // Change this to any port (1024-65535)
```

Then rebuild the project.

---

## 🎨 Color Scheme

| Color | Usage |
|-------|-------|
| 🔴 Red | Login/Logout messages |
| 🟡 Yellow | Server connection info |
| 🟢 Green | Success messages |
| 🔵 Cyan | Received chat messages |
| 🟣 Magenta | Your input prompt |

---

## ❌ Troubleshooting

### **1. "Cannot connect to server"**
```
Error connecting to server
```

**Solution:**
- ✅ Verify server is running
- ✅ Check server IP address is correct
- ✅ Ensure firewall allows port 9999
- ✅ Try localhost (127.0.0.1) first

### **2. "Error binding socket"**
```
Error binding socket
```

**Solution:**
- Port 9999 is already in use
- Change port in `src/common/protocol.h`
- Rebuild and run

### **3. Build errors on Windows**
```bash
# If CMake can't find Visual Studio:
cmake -G "Visual Studio 17 2022" -A x64 ..
```

### **4. Build errors on Linux**
```bash
# Install missing dependencies:
sudo apt-get install build-essential cmake

# If pthread not found:
sudo apt-get install libpthread-stubs0-dev
```

### **5. Clients can't see each other's messages**
- Make sure all clients are connected to the same server
- Check server console for [CHAT] messages
- Verify message appears in chat_log.txt

---

## 🚀 Running Multiple Instances Locally

**Terminal 1 (Server):**
```bash
cd build/Release
.\ChatApp_Server.exe
```

**Terminal 2 (Client 1):**
```bash
cd build/Release
.\ChatApp_Client.exe
# Enter: 127.0.0.1
# Name: Alice
```

**Terminal 3 (Client 2):**
```bash
cd build/Release
.\ChatApp_Client.exe
# Enter: 127.0.0.1
# Name: Bob
```

**Terminal 4 (Client 3):**
```bash
cd build/Release
.\ChatApp_Client.exe
# Enter: 127.0.0.1
# Name: Charlie
```

---

## 📋 Features Checklist

✅ Multi-client networking  
✅ Client name registration  
✅ Chat messages with sender names  
✅ Server-side logging to chat_log.txt  
✅ Cross-platform support (Windows, Linux, macOS)  
✅ Works in Visual Studio 2022  
✅ Works in VS Code  
✅ Clean folder structure  
✅ No unwanted files  
✅ Colored console output  

---

## 📝 License

Open source - Feel free to modify and distribute

---

**Ready to chat across multiple devices! 🎉**
