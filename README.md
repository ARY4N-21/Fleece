# FLEECE
  ## A Simple Chat Application using Socket Programming

This project serves as a basic tutorial for implementing a chat application using socket programming in C++.

## Overview
This project consists of two main files:

- `server.cpp` : Contains the server-side code for the chat application.
- `client.cpp` : Contains the client-side code for the chat application.


## Getting Started

Follow these steps to compile and run the chat application:

1. ***Compile the Server Code***

        g++ server.cpp -o server

2. ***Compile the Client Code***

        g++ client.cpp -o client
3. ***Run the Server***

        ./server
4. ***Run the Client***

      - Open one or more terminals, depending on the number of clients you want to simulate.
      - In each terminal, run:
        
                ./client

5. ***Start the Conversation***
    - Once the server and clients are running, you can start sending messages between them.
    - Type a message in the client terminal and press Enter to send it to the server.
    - The server will receive the message and broadcast it to all connected clients.
      
6. ***Stopping the Server***

    - To stop the server, use `Ctrl + C` in the terminal where the server is running.
7. ***Exiting a Client***

    - To exit a client, simply type exit in its terminal and press Enter.

## Acknowledgments
This project was inspired by the desire to provide a simple and educational example of socket programming in C++. We hope it serves as a useful learning resource for those interested in network programming.

