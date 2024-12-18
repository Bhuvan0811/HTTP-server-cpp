#include <iostream>
#include <winsock2.h>   // For socket functionality on Windows
#include <ws2tcpip.h>   // For sockaddr_in and htons, etc.
#include <cstring>      // For strlen
using namespace std;

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Define server address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    // Send a message to the server
    string method = "GET";
    string URL = "./index.html";
    string version = "HTTP/1.1";
    string headers = "Accept: html\nHost: 127.0.0.1";
    string body = "This is a test Body";

    string request = method + " " + URL + " " + version + "\r\n" + headers + "\r\n" + body;
    char message[1024] = {0};
    char buffer[1024] = {0};

    strcpy(message, request.c_str());// c_str() converts it to constant as second arg is needed to be a constant

    // Send the message with correct length (using strlen to get the string's length)
    send(clientSocket, message, strlen(message), 0);
    recv(clientSocket, buffer, sizeof(buffer), 0);// do not use strlen
    cout << buffer << endl;
    // Close the client socket and clean up Winsock
    closesocket(clientSocket);
    WSACleanup();
}
