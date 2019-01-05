#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string> 
#include <thread>
#include <tuple>
#include <vector>

#include "User.h"
#include "Socket.h"
#include "ServerSocket.h"
#include "Commands.h"

using namespace std;


int port;
string db_path;
int guest_id = 0;
vector<unique_ptr<thread>> thread_list;

map<string, vector<string>> user_list;
map<string, vector<User>> listo_channels;


// Open and read the config files
int start() {

    // Open configuration file
    ifstream conf; 
    string line;
    conf.open("chatserver.conf");
    if (!conf) {
        cout << "chatserver.conf not found in current directory" << endl;
        return -1;
    }

    // Read port number and db_path
    conf >> line >> port >> line >> db_path;

    // Read users.txt
    ifstream users;
    users.open(db_path + "users.txt");
    if (!users) {
        cout << "ERROR: File not found: users.txt" << endl;
        return -1;
    }

    // Read registered users
    while(getline(users, line)) {
        istringstream ss(line);
        string user, password, level, banned;
        ss >> user >> password >> level >> banned;
        user_list[user].push_back(password); 
        user_list[user].push_back(level); 
        user_list[user].push_back(banned);
    }

    return 0;
}


// Remove user from their channel when they disconnect
void remove(User &user) {
    for (uint i = 0; i < listo_channels[user.getChan()].size(); i++) {
        if (listo_channels[user.getChan()][i].getName() == user.getName()) {
            listo_channels[user.getChan()].erase(listo_channels[user.getChan()].begin() + i);
            break;
        }
    }
}


// Log the existing user into the server
void loginUser(User &user) {

	string banned  = string("Unfortunately, admins have deemed it necessary to ban you ") +
		("from this server! Access is denied!\n");
    // If a user is banned, don't let them log in
    if(user_list[user.getName()][2] == "true") {
        user.sendString(banned);
        user.disconnect();
        remove(user);
    }

    // Get password
    user.sendString("Enter your password\n");
    string password = user.recvString();

    // Uncomment this out to make it work on terminal
    password = password.substr(0, password.size() - 1);

    // Check if correct
    while (user_list[user.getName()][0] != password) {
        user.sendString("Password is incorrect, please try again\n");
        password = user.recvString();
        password = password.substr(0, password.size() - 1);
    }

    // User is logged in
    if (user_list[user.getName()][1] == "admin") {
        user.sendString("Admin login successful!\n");
        user.setLvl("admin");
    }
    else if (user_list[user.getName()][1] == "sysop") {
        user.sendString("Sysop login successful!\n");
        user.setLvl("sysop");
    }
    else if (user_list[user.getName()][1] == "channelop") {
        user.sendString("Channelop login successful!\n");
        user.setLvl("channelop");
    }
    else {
        user.sendString("Login successful!\n");
        user.setLvl("user");
    }
}

// Register a new user
void registerUser(User &u) {

    // Set password
    u.sendString("Set a password for " + u.getName() + ":\n");
    string password = u.recvString();
    u.setPass(password.substr(0, password.size() - 1));

    // Add to users.txt
    ofstream out;
    out.open(db_path + "users.txt", fstream::app);
    out << u.getName() << " " << u.getPass() << " user false\n";

    // Add to users map
    user_list[u.getName()].push_back(u.getPass());
    user_list[u.getName()].push_back("user");
    user_list[u.getName()].push_back("false");

    // Send confirmation
    u.sendString("Registered on server as " + u.getName() + ".\n");
    u.setLvl("user");
    u.sendString("Connected to the server!\n");
}

// Handle the new user's authentication for the server
void validate(User &u) {

    // Get username
    string user = u.recvString();

    // Create guest user
	if (user == "guest\n") {
        u.setUsername(guest_id);
        u.setLvl("user");
        u.sendString("^" + u.getName() + "\n");
        u.sendString("Connected to server!\n\n");
    }
    else {
        // Set username
        u.setUsername(user);

        // Register new user
        if (user_list[u.getName()].empty()) registerUser(u);

        // Log in existing user
        else loginUser(u);
    }

    // Add to default channel
    listo_channels[u.getChan()].push_back(u);
    cout << u.getName() << " has joined the chat!\n";
    for (uint i = 0; i < listo_channels[u.getChan()].size(); i++)
        if (listo_channels[u.getChan()][i].getName() != u.getName())
            listo_channels[u.getChan()][i].sendString(u.getName() + " has joined the channel.\n");
}

// Handle the client connection
int cclient(shared_ptr<Socket> clientSocket) {

    string msg;
    string response;
	
	// Create user and register as guest or member
	User u(clientSocket);
    
	validate(u);

    // While client is connected
    while (true) {

        // Get message
        msg = u.recvString();
        response = parseCommand(u, listo_channels, msg);

        // Kill server if prompted to die
        if (response == "/DIE\n") {
			exit(EXIT_FAILURE);
		}

        // Disconnect client if prompted to quit
        if (response == "/QUIT\n") {
            remove(u);
            return 0;
        }

        // Send the response
        else if (response != "") {
			thread child(&User::sendString, &u, response);
            child.join();
        }  
    }
    return 0;
}

int main(int argc, char * argv[]) {

    // Read configuration files
    if (start() < 0) {
		exit(EXIT_FAILURE);
	}

    // Start server
    cout << "Server sucessfully started on port " << port << '\n'; 
    ServerSocket server(port);
    server.bindSocket(); 
    server.listenSocket(); 
    cout << "Waiting to receive connections..." << endl << endl;
  
    // Add to thread list
    while (true) { 
        shared_ptr<Socket> clientSocket;
        int val;
        tie(clientSocket,val) = server.acceptSocket();
        unique_ptr<thread> t = make_unique<thread>(cclient, clientSocket); 
        thread_list.push_back(move(t));
    }

    // Make sure to join the threads!
    for (auto& t: thread_list) t.get()->join();

    return 0; 
}
