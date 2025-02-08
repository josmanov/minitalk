# 📡 Minitalk - Unix Communication

Minitalk is a **42 project** that explores inter-process communication (IPC) using **signals**. The goal is to send and receive messages between a client and a server using Unix signals.

---

## ⚙️ Installation

1. **Clone the repository**:

   ```bash
   git clone https://github.com/josmanov/minitalk.git
   ```

2. **Enter the project directory**:

   ```bash
   cd minitalk
   ```

3. **Compile the project**:

   ```bash
   make
   ```

   - To clean up compiled files:
     ```bash
     make clean
     ```
   - To fully clean up the repository:
     ```bash
     make fclean
     ```
   - To recompile from scratch:
     ```bash
     make re
     ```

---

## 🚀 Usage

### **1️⃣ Start the server**

Run the server first to listen for messages:

```bash
./server
```

It will display its **PID** (Process ID), which you need for the client.

### **2️⃣ Send a message from the client**

Use the client to send a message to the server:

```bash
./client <server_pid> <"Message">
```

Example:

```bash
./client 424242 ""Hello, Minitalk!""
```

The message will be sent **character by character** using Unix signals.

---

## 📡 How It Works

Minitalk uses **SIGUSR1** and **SIGUSR2** to communicate between processes:

- **SIGUSR1** represents a binary **0**.
- **SIGUSR2** represents a binary **1**.
- The client converts each character into **binary** and sends signals to the server.
- The server reconstructs the message and prints it.

---

## 🌍 Built With

- **C** – The project is written in **pure C**.
- **Unix Signals** – Used for communication between processes.
