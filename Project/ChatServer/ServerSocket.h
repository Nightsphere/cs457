#pragma once

#include <arpa/inet.h>
#include <memory>
#include <netinet/in.h>
#include <string>
#include <strings.h>
#include <sys/socket.h> 
#include <tuple> 
#include <unistd.h>

#include "Socket.h"

using namespace std; 


class ServerSocket {

public:
    ServerSocket(ushort portNumber); 
    ServerSocket(string networkAddress, ushort portNumber);
    int bindSocket();
    int listenSocket();
    tuple<shared_ptr<Socket>,int> acceptSocket();
    
private: 
    void init();
    void setSocketOptions();

    string address;
    ushort port;
    int serverSocket;
    struct sockaddr_in serverAddress; 
    struct in_addr addr;
};
