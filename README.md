# HTTP Server in C++ (Socket Programming)

This project implements a basic HTTP server and client using socket programming in C++. It aims to understand how the HTTP protocol works under the hood by directly interacting with TCP sockets, rather than relying on external libraries such as Express.js.

## Purpose of the Project

The project is designed to deepen understanding of HTTP protocol workings. Typically, in web development, frameworks like Express.js abstract away low-level protocols, but in this project, the focus is on implementing HTTP requests and responses using TCP connections.

### Key Concepts:
- **Socket Programming**: For low-level network communication over TCP.
- **TCP (Transmission Control Protocol)**: A connection-oriented protocol that provides reliable, ordered, and error-checked delivery of data between clients and servers.
- **HTTP (Hypertext Transfer Protocol)**: An application layer protocol that operates over TCP to facilitate communication between clients and servers.

## Project Overview

- **Server**: Listens for incoming HTTP requests and sends back responses.
- **Client**: Makes HTTP requests to the server and receives responses.

The main goal is to manually manage HTTP requests and responses, offering a better understanding of the data exchange that occurs in web browsers and servers.

## Compilation Instructions:

To compile the server and client programs, you can use the following commands:


### For server
g++ -std=c++11 -o http_server server.cpp -lws2_32

### For client
g++ -std=c++11 -o http_client client.cpp -lws2_32

## Running the Application:
Start the server on one terminal:
./server.exe

Start the client on a separate terminal:
./client.exe

The server needs to be running before starting the client. The client will send HTTP requests to the server, and the server will respond accordingly.

## Future Work
-Implement actual functionality for POST, PUT, and DELETE HTTP methods.
-Handle multiple client requests concurrently using better threading techniques.

This project was created for educational purposes to demonstrate basic HTTP, socket programming, and client-server communication. By directly interacting with these protocols, one can better understand how modern web frameworks build on these foundations.

Feel free to contribute improvements or extensions to this project!