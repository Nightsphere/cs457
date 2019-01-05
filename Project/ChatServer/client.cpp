#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include <vector>

#include "Socket.h"

using namespace std;


string host;
string user = "guest";
int port;
string config_file;
string log_file;

int sock;
struct sockaddr_in addr;
char buff[2048];
mutex sendMutex;
mutex recvMutex;

string channel = "General";


// connect(): Connect to server
int connect() {

    // Start the client socket
    cout << endl << "Connecting to " << host << ":" << port << "... " << endl;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Unable to create socket. \n\n");
        return -1;
    }
    
    // Do some stuff
    memset(&addr, '0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
       
    // Set the host addr
    if(inet_pton(AF_INET, host.c_str(), &addr.sin_addr) <= 0) {
        printf("Invalid addr. \n\n");
        return -1;
    }
    
    // Connect to the socket
    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        printf("Unable to connect to server. \n\n");
        return -1;
    }
	
	// Send username to the server
    write(sock, string(user + "\n").c_str(), string(user + "\n").size());
    return 0;
}


// Read data from the server
void rData() {
    while (true) {
        memset(&buff, 0, sizeof(buff));
        recv(sock, (char *)&buff, sizeof(buff), 0);

        // If quit is 
        if (string(buff).find("/QUIT\n") != std::string::npos) {
            cout << "Closing connection..." << endl << endl;
            close(sock); exit(0);
        }

        // Guest username
        else if (buff[0] == '^') {
            user = string(buff);
            user = user.substr(1, user.size() - 2);
            cout << "Your username is " << user << "." << endl;
        }

        // Switch channels
        else if (buff[0] == '@') {
            string old = string(buff);
            old = old.substr(1, old.size() - 2);
            cout << "You have been removed from the @" << old << " channel!" << endl;
            channel = "general";
            string join = "/join general\n";
            write(sock, join.c_str(), join.size());
        }
        else cout << buff;
    }
}


// Write data to server
void wData() {
    while(true){
        string s;
        getline(cin, s);
        s += "\n";
        write(sock, s.c_str(), s.size());
    }
}

int main(int argc, char *argv[]) {

    // Parse arguments
    int opt;
    cout << endl;
    while((opt = getopt(argc, argv, "h:u:p:c:L:")) != EOF) {
        switch(opt) {
            case 'h': host = optarg; break;
            case 'u': user = optarg; break;
            case 'p': port = stoi(optarg); break;
            case 'c': config_file = optarg; break;
            case 'L': log_file = optarg; break;
            case '?': fprintf(stderr, "usage is \n -h hostname \n -u username \n -p server port \n -c configuration file \n -t run test file \n -L log_file_name \n\n"); exit(-1);
        }
    }

    // Connect to the server
    if (connect() < 0) {
        exit(EXIT_FAILURE);
    }

    thread rThread(&rData);
    thread wThread(&wData);

    wThread.join();
    rThread.join();

    return 0; 
}
