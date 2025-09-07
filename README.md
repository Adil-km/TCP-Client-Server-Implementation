
# TCP Client–Server Simulation in C

This project demonstrates a **TCP client-server implementation** in the **C programming language**.  

- Run the **server-side code** on one terminal.  
- Start the **client-side code** on another terminal.  
- The client establishes a connection with the server.  
- They can then **send and receive data** between each other.  

**Note:** This implementation is designed to work **only on Linux** systems.  

---

## How to Compile and Run

### 1. Compile the server code:

```bash
gcc server.c -o server
```

### 2. Compile the client code:

```bash
gcc client.c -o client
```

### 3. Run the server code:

```bash
./server
```

### 4. Run the client code (in a separate terminal):

```bash
./client
```

---

## 🛠️ Troubleshooting

Sometimes the server process may still be running in the background, which can prevent you from starting a new server. Use the following commands:

### Find processes using port 8080:

```bash
lsof -i :8080
```

### Kill the running server process:

```bash
kill -9 <PID>
```

Replace `<PID>` with the process ID shown in the output of the `lsof` command.

## Demo video


https://github.com/user-attachments/assets/fa9281a4-fdd5-446e-b22c-f5ecab1ad9dd



