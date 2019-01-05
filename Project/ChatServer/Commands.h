#pragma once

#include <bits/stdc++.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "User.h"
#include "Socket.h"

using namespace std;


string parseCommand(User &user, map<string, vector<User>> &listo_channels, const string &msg);

string DIE(User &user, map<string, vector<User>> &listo_channels);
string HELP();
string INFO();
string INVITE(User &user, map<string, vector<User>> &listo_channels);
string ISON(map<string, vector<User>> &listo_channels);
string JOIN(User &user, map<string, vector<User>> &listo_channels);
string KNOCK(User &user, map<string, vector<User>> &listo_channels);
string KICK(User &user, map<string, vector<User>> &listo_channels);
string KILL(User &user, map<string, vector<User>> &listo_channels);
string LIST(map<string, vector<User>> &listo_channels);
string NICK(User &user, map<string, vector<User>> &listo_channels);
string NOTICE(User &user, map<string, vector<User>> &listo_channels);
string OPER(map<string, vector<User>> &listo_channels);
string PING();
string PONG();
string PRIVMSG(User &user, map<string, vector<User>> &listo_channels);
string QUIT(User &user, map<string, vector<User>> &listo_channels);
string RULES();
string SETNAME(User &user, map<string, vector<User>> &listo_channels);
string SILENCE();
string TIME();
string USER(User &user);
string USERHOST(User &user);
string USERIP(User &user);
string USERS(User &user, map<string, vector<User>> &listo_channels);
string VERSION();
string WHO(User &user);
string WHOIS(map<string, vector<User>> &listo_channels);

bool userInChannel(User &user, map<string, vector<User>> &listo_channels);
void sendToAll(User user, map<string, vector<User>> &listo_channels, string msg);
void sendToAllExcept(User user, map<string, vector<User>> &listo_channels, string msg, string username);
