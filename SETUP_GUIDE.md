# Quick Setup Guide - Chatting Application

## 🎯 Quick Start (5 Minutes)

### Step 1: Prerequisites
```bash
# Windows: Install Visual Studio 2022 + CMake
# Linux: sudo apt-get install build-essential cmake
# macOS: brew install cmake
```

### Step 2: Clone Repository
```bash
git clone https://github.com/Anuradhaprasad2007/chatting-application.git
cd chatting-application
```

### Step 3: Build
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Step 4: Run Server
```bash
# Windows:
.\Release\ChatApp_Server.exe

# Linux/macOS:
./ChatApp_Server
```

### Step 5: Run Client(s)
```bash
# In new terminal(s):
# Windows:
.\Release\ChatApp_Client.exe

# Linux/macOS:
./ChatApp_Client
```

### Step 6: Connect & Chat
- Enter server IP (127.0.0.1 for local, or server's IP for remote)
- Enter your name
- Start typing!

---

## 🔗 Network Connection

### Local Testing (Same PC)
```
Server IP: 127.0.0.1
Port: 9999
```

### Remote Connection (Different PCs)
```
1. Find server IP:
   Windows: ipconfig
   Linux: ifconfig
   macOS: ifconfig

2. Allow firewall port 9999

3. Connect with server's IP address
```

---

## 📂 Output Files

- **Executables**: `build/Release/`
- **Chat Logs**: `chat_log.txt` (created where server runs)

---

## ✅ Test Checklist

- [ ] Server starts without errors
- [ ] Client connects to server
- [ ] Can enter name
- [ ] Can type messages
- [ ] Messages appear on other clients
- [ ] chat_log.txt is created
- [ ] Timestamps are logged
- [ ] Can exit with 'exit' command
