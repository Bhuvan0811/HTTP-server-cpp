#include <iostream>
#include <vector>
#include <winsock2.h>   // For socket functionality on Windows
#include <ws2tcpip.h>   // For sockaddr_in and htons, etc.
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <pthread.h>
using namespace std;
// thread function is of signature void*(*)(void*)
void* readFile(void* URL){
    string path = *static_cast<string*>(URL);
    ifstream f(path);
    string* s = new string();
    if(!f.is_open()){
        cerr << "Error reaching the resource!!" << endl;
        *s = "\r";
    }
    else {
        string temp;
        while(getline(f, temp)) *s += temp + '\n';  
    }
    return static_cast<void*>(s);
}
unordered_map<int, string> extractInfo(const char buffer[]){
    stringstream s(buffer);
    unordered_map<int, string> lines;
    string line;
    string para = "";
    int i = 0;
    while(getline(s, line, '\n')){
        if(line.size() && line[line.size() - 1] == '\r') {
            line.pop_back();
            para += line;
            lines[i] = para;
            para = "";
            i++;
        }       
        else  para += line +"\n";
    }
    if(para.size()) para.pop_back();
    lines[2] = para;
    return lines;
}
string makeResponse(const string& body, const string& version, const int& statusCode, const string& statusMessage, const string& headers){
    string response = version + " " + to_string(statusCode) +
     " " + statusMessage + "\r\n" + headers +"\r\n" + body;

    return response;
}

string GET(string URL){
    pthread_t fileReadThread;
    pthread_create(&fileReadThread, NULL, readFile, static_cast<void*>(&URL));
    void* text;
    pthread_join(fileReadThread, &text);
    string info = *static_cast<string*>(text);
    delete static_cast<string*>(text);
    return info;
}
string PUT(){
    return "d";
}
string POST(){
    return "d";
}
string Delete(){
    return "d";
}

int main() {
    // Initialize Winsock
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    listen(serverSocket, 5);

    int clientSocket = accept(serverSocket, nullptr, nullptr);
    
    string methodName, URL, version, body = "", res = "", statusMessage = "", headers = "";
    int statusCode = 0;
    char response[1024] = {0};
    char buffer[1024] = { 0 };
    unordered_map<int, string> lines;

    recv(clientSocket, buffer, sizeof(buffer), 0);
    lines = extractInfo(buffer);
    stringstream s(lines[0]);
    s >> methodName >> URL >> version;

    // for(auto line: lines) cout << line.first << endl << line.second << endl;
    // cout <<"---" <<  methodName << "---" <<URL <<"---";
    if(methodName == "GET") {
        body = GET(URL);
        // cout<< body;
        if(body == "\r"){
            statusCode = 404;
            statusMessage = "Not Found";
        }
        else {
            statusCode = 200;
            statusMessage ="OK";
            headers = "Content-Type: Text/HTML\nContent-Length: " + to_string(body.size());
        }
    }
    else if(methodName == "POST") {
        statusCode = 501;
        statusMessage = "Not Implemented.";
        POST();
    }
    else if(methodName == "PUT") {
        statusCode = 501;
        statusMessage = "Not Implemented.";
        PUT();
    }
    else if(methodName == "DELETE") {
        statusCode = 501;
        statusMessage = "Not Implemented.";
        Delete();
    }
    else ;
    
    res = makeResponse(body, version, statusCode, statusMessage, "");
    strcpy(response, res.c_str());
    cout << response << endl;
    send(clientSocket, response, strlen(response), 0);

    closesocket(serverSocket);
    WSACleanup();
}
