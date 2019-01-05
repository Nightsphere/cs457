#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>

#include "Socket.h"

using namespace std;


class User {

    public:
        User(shared_ptr<Socket> cSocket): clientSocket(cSocket) {}
		User(){}

        string recvString();
        void sendString(const string& data);
        void disconnect();

        void setUsername(string username);
        void setUsername(int& id) {
            username = "guest" + to_string(id); id++;
        }
        void setPass(string pswd) {
            password = pswd;
        };
        void setChan(string chn) {
            channel = chn;
            }
        void setLvl(string lvl) {
            level = lvl;
            }

        string getName() {
            return username;
        }
        string getHostname() {return "127.0.0.1";}
        string getPass() {return password;}
        string getChan() {return channel;}
        string getLevel() {return level;}
		shared_ptr<Socket> getSocketPointer() {return clientSocket;}

    private:
        string username, password, level;
        bool banned = false;
        string channel = "general";
        shared_ptr<Socket> clientSocket;

};
