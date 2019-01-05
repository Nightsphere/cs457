#include "Socket.h"

using namespace std; 


// connectSocket(): Connect client to the server
int Socket::connectSocket(string hostname, int port) {

    // Create the socket
    if ((userSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Unable to create socket. \n\n");
        return -1;
    }
    
    // Create sockaddr_in struct
    memset(&userAddress, '0', sizeof(userAddress)); 
    userAddress.sin_family = AF_INET; 
    userAddress.sin_port = htons(port); 
       
    // Set host address
    if(inet_pton(AF_INET, hostname.c_str(), &userAddress.sin_addr) <= 0) {
        printf("Invalid address. \n\n");
        return -1;
    }
    
    // Connect to socket
    if (connect(userSocket, (struct sockaddr *)&userAddress, sizeof(userAddress)) < 0) {
        printf("Unable to connect to server. \n\n");
        return -1;
    }

    // Connection successful!
    printf("Connected to server! \n\n");
    return 0;
};


// Set, Get, and Close the socket
void Socket::setSocket(int sckt) {
    userSocket=sckt;
};

int Socket::getSocket() {
    return userSocket;
};

int Socket::closeSocket() {
    return close(userSocket);
};


// getAddressSize(): Get the length of the pointer
socklen_t Socket::getAddressSize() {
    return sizeof(userAddress);
};


void Socket::setUserInfoIPv4(string address, uint16_t port) {
    clientAddressIPv4 = address;
    clientPortIPv4 = port; 
};


// recvString(): Receive incoming message
tuple<string,ssize_t> Socket::recvString(int buffSize, bool useMutex) {
    char stringbuff[buffSize]; 
    memset(stringbuff, 0, sizeof(stringbuff));
    ssize_t recvMsgSize;
    if (useMutex) {
        lock_guard<mutex> lock(recvMutex);
        recvMsgSize = recv(userSocket, stringbuff, buffSize, 0); 
    }    
    else {
        recvMsgSize = recv(userSocket, stringbuff, buffSize, 0); 
    }
    return make_tuple(string(stringbuff),recvMsgSize);     
};


// sendString(): Send outgoing message
ssize_t Socket::sendString(const string & data, bool useMutex) {

    const char *s = data.c_str();
    ssize_t rval; 
    if (useMutex) {
       lock_guard<mutex> lock(sendMutex);
       rval = send(userSocket, s, strlen(s), 0);
    }
    else {
       rval = send(userSocket, s, strlen(s), 0);     
    }

    return rval;
}

string Socket::getUniqueIdentifier() { 
     string identifier  = "[" + clientAddressIPv4 + "," + to_string(clientPortIPv4) + "]"; 
     return identifier; 
};


// getAddressPointer(): Get the address pointer
struct sockaddr * Socket::getAddressPointer() {
    return ((struct sockaddr *) &userAddress);
};
