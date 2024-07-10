# Single Server and Multiple Clients Network

### Introduction
This project demonstrates a simple network client-server application in C that facilitates communication between multiple clients using TCP/IP. The server listens for connections from clients, manages these connections, and broadcasts messages received from one client to all other connected clients. This setup provides a foundational understanding of socket programming and multithreading to handle concurrent operations in a networked environment.

# Server Key Functions:

### Socket Initialization and Binding:
- The server initializes a master socket, binds it to a specified port, and listens for incoming connections.
### Client Management:
- An array client_socket keeps track of connected clients.
- Uses the select function to monitor the master socket for new connections and all client sockets for incoming messages.
### Handling New Connections:
- When a new client connects, it is added to the client_socket array.
- Sends a welcome message ("hai!client") to the new client.
- Message Handling and Broadcasting:
### Reads messages from clients.
- If a message is "exit", the client is disconnected, and a notification is broadcasted to remaining clients.
- If a message is not "exit", it is broadcasted to all other connected clients.

# Client Key Functions

### Socket Initialization and Connection:
- The client initializes a socket and connects to the server.
### Multithreading for Concurrent Operations:
-Uses pthreads to handle reading from and writing to the server concurrently.
### Sending Messages:
- Reads input from the standard input and sends it to the server.
- Checks for the "exit" command to terminate the connection.
### Receiving Messages:
- Reads messages from the server and prints them to the standard output.