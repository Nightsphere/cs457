#include "User.h"

string User::recvString() {
    return get<0>(clientSocket.get()->recvString());
}


void User::sendString(const string& data) {
    clientSocket.get()->sendString(data);
}

void User::disconnect() {
    clientSocket.get()->closeSocket();
}

void User::setUsername(string username) {
	username.erase(remove(username.begin(), username.end(), '\n'), username.end());
    this->username = username;
}
