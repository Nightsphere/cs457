#include "Commands.h"


// Command arguments
vector<string> command_args;

// Read command and perform action
string parseCommand(User &user, map<string, vector<User>> &listo_channels, const string &msg) {

    // Parse command and command arguments using a stringstream
    if (msg.at(0) == '/') {
        command_args.clear();
        istringstream ss(msg); 
        string command;
        string temp;
        ss >> command;
        while (ss >> temp) command_args.push_back(temp);

        // Transform command to upper case
        transform(command.begin(), command.end(), command.begin(), ::toupper);

        // List of my implemented commands
        if (command == "/DIE") {
            return DIE(user, listo_channels);
        }
        if (command == "/HELP") {
            return HELP();
        }
        if (command == "/INFO") {
            return INFO();
        }
        if (command == "/INVITE") {
            return INVITE(user, listo_channels);
        }
        if (command == "/ISON") {
            return ISON(listo_channels);
        }
        if (command == "/JOIN") {
            return JOIN(user, listo_channels);
        }
        if (command == "/KICK") {
            return KICK(user, listo_channels);
        }
        if (command == "/KILL") {
            return KILL(user, listo_channels);
        }
        if (command == "/KNOCK") {
            return KNOCK(user, listo_channels);
        }
        if (command == "/LIST") {
            return LIST(listo_channels);
        }
        if (command == "/NICK") {
            return NICK(user, listo_channels);
        }
        if (command == "/NOTICE") {
            return NOTICE(user, listo_channels);
        }
        if (command == "/OPER") {
            return OPER(listo_channels);
        }
        if (command == "/PING") {
            return PING();
        }
        if (command == "/PONG") {
            return PONG();
        }
        if (command == "/PRIVMSG") {
            return PRIVMSG(user, listo_channels);
        }
        if (command == "/QUIT") {
            return QUIT(user, listo_channels);
        }
        if (command == "/RULES") {
            return RULES();
        }
        if (command == "/SETNAME") {
            return SETNAME(user, listo_channels);
        }
        if (command == "/TIME") {
            return TIME();
        }
        if (command == "/USER") {
            return USER(user);
        }
        if (command == "/USERHOST") {
            return USERHOST(user);
        }
        if (command == "/USERIP") {
            return USERIP(user);
        }
        if (command == "/USERS") {
            return USERS(user, listo_channels);
        }
        if (command == "/VERSION") {
            return VERSION();
        }
        if (command == "/WHO") {
            return WHO(user);
        }
        if (command == "/WHOIS") {
            return WHOIS(listo_channels);
        }
        else {
            return "Invalid command. For a list of commands type /HELP.\n";
        }
    }

    // Regular message (for terminal)
    // else sendToAll(user, listo_channels, "[@" + user.getChan() + ": " + user.getName() + "] " + msg);
    // Regular message (for GUI)
    else sendToAll(user, listo_channels, user.getName() + " says: " + msg);
    return "";
}

// Shut down server (admin privileges only)
string DIE(User &user, map<string, vector<User>> &listo_channels) {
    if (user.getLevel() == "admin") {
        sendToAll(user, listo_channels, user.getName() + " has shut down the server!\n");
        sendToAll(user, listo_channels, "/QUIT\n");
        user.sendString("Successfully shut down server.\n");
        return "/DIE\n";
    }
    else {
        return "/DIE: You do not have the required privileges to run this command!\n";
    }
}


// Get list of commands
string HELP() {
    string help = "\nThe available IRC commands are as follows: \n" +
    string("  /DIE: \n") +
    string("      Parameters:   [password]\n") + 
    string("      Description:  Shuts down the server if the client has admin privileges\n") +
    string("  /HELP: \n") +
    string("      Parameters:   none\n") + 
    string("      Description:  Displays a list of available commands\n") +
    string("  /INFO: \n") +
    string("      Parameters:   none\n") + 
    string("      Description:  Diplays information about the creator of the program\n") +
    string("  /INVITE: \n") +
    string("      Parameters:   <nickname> <channel>\n") + 
    string("      Description:  Sends an invitation to [username] requesting that they join the [channel]\n") +
    string("  /ISON: \n") +
    string("      Parameters:   <nickname>\n") + 
    string("      Description:  Displays whether [username] is online\n") +
    string("  /JOIN: \n") +
    string("      Parameters:   <channel>{,<channel>}\n") + 
    string("      Description:  Allows you to join [channel]\n") +
    string("  /KICK: \n") +
    string("      Parameters:   <channel> <user> [<comment>]\n") + 
    string("      Description:  Removes [username] from the chat if client has admin or sysop privileges\n") +
    string("  /KILL: \n") +
    string("      Parameters:   <nickname> <comment>\n") + 
    string("      Description:  Removes [username] from the chat if client has admin or sysop privileges\n") +
    string("  /KNOCK: \n") +
    string("      Parameters:   <channel>[message]\n") + 
    string("      Description:  Knocks on a channel by sending an optional message or a default message to all users\n") +
    string("  /LIST: \n") +
    string("      Parameters:   [<channel>{,<channel>} [<server>]]\n") + 
    string("      Description:  Displays a list of all currently available channels\n") +
    string("  /NICK: \n") +
    string("      Parameters:   <new nickname>\n") + 
    string("      Description:  Changes your username and checks that it's not already taken or tells you what it already\n") +
    string("  /NOTICE: \n") +
    string("      Parameters:   <nickname> <text>\n") + 
    string("      Description:  Sends a private message to [username]\n") +
    string("  /OPER: \n") +
    string("      Parameters:   <user>\n") + 
    string("      Description:  Will check if username is online and returns what kind of privelege they have, which could be\n") +
    string("  /PING: \n") +
    string("      Parameters:   none\n") + 
    string("      Description:  Responds with 'PONG'\n") +
    string("  /PONG: \n") +
    string("      Parameters:   none\n") + 
    string("      Description:  Responds with 'PING'\n") +
    string("  /PRIVMSG: \n") +
    string("      Parameters:   <receiver> [message]\n") + 
    string("      Description:  Sends a private message to [username]\n") +
    string("  /QUIT: \n") +
    string("      Parameters:   [message]\n") + 
    string("      Description:  Ends connection and tells everyone in the current channel you left, displaying the optional\n") +
    string("  /RULES: \n") +
    string("      Parameters:   none\n") + 
    string("      Description:  Shows the server rules\n") +
    string("  /SETNAME: \n") +
    string("      Parameters:   [new name]\n") + 
    string("      Description:  Same as command [11]\n") +
    string("  /TIME: \n") +
    string("      Parameters:   \n") + 
    string("      Description:  Shows the current time\n") +
    string("  /USER: \n") +
    string("      Parameters:   none\n") + 
    string("      Description:  Displays the client's username\n") +
    string("  /USERHOST: \n") +
    string("      Parameters:   \n") + 
    string("      Description:  Displays the hostname (default is 2000)\n") +
    string("  /USERS: \n") +
    string("      Parameters:   [server]\n") + 
    string("      Description:  Displays everyone currently online\n") +
    string("  /USERIP: \n") +
    string("      Parameters:   none\n") + 
    string("      Description:  Displays your IP address\n") +
    string("  /VERSION: \n") +
    string("      Parameters:   [<server>]\n") + 
    string("      Description:  Displays the version of the chat server\n") +
    string("  /WHO: \n") +
    string("      Parameters:   none\n") + 
    string("      Description:  Shows your username.\n") +
    string("  /WHOIS: \n") +
    string("      Parameters:   [username]\n") + 
    string("      Description:  Displays your username and the hostname of the server\n");
    return help;
}


// INFO: get server information
string INFO() {
    string info = "Welcome!\nChat Server 1.0\nCreated by Josh Keahey";
    return info; 
}


// Invite a user to the channel
string INVITE(User &user, map<string, vector<User>> &listo_channels) {

    // Check for correct number of arguments
    if (command_args.size() == 2) {

        bool channel_exists = false;
        bool is_member = false;
        string username = command_args[0];
        string channel = command_args[1];

        // Check if channel exists
        for(map<string, vector<User>>::iterator it = listo_channels.begin(); it != listo_channels.end(); it++)
            if ((it->first) == channel) channel_exists = true;
        if (!channel_exists) {
            return "/INVITE: Channel " + channel + " doesn't exist. You can create it by running the command /JOIN " + channel + ".\n";
        }

        // Check if user is in channel
        for (ushort i = 0; i < listo_channels[channel].size(); i++)
            if (listo_channels[channel][i].getName() == user.getName())
                is_member = true;
        if (!is_member) {
            return "/INVITE: You must be a member of @" + channel + " to invite other users.\n";
        }

        // Search for user and send message
        for(map<string, vector<User>>::iterator it = listo_channels.begin(); it != listo_channels.end(); it++) {
            for (ushort i = 0; i < it->second.size(); i++) {
                if ((it->second)[i].getName() == username) {
                    (it->second)[i].sendString(user.getName() + " has invited you to join @" + channel + "! Join by running the command /JOIN " + channel + ".\n");
                    return "Invite sent to " + username + ".\n";
                }
            }
        }

        // If the user wasn't found
        return "/INVITE: User " + command_args[0] + " was not found.\n";
    }
    else {
        return "/INVITE: Please specify a user and a channel.\n";
    }
}


// Returns online usernames
string ISON(map<string, vector<User>> &listo_channels) {
    if (command_args.size() > 0){
        string ison; bool found;

        // Search for user in listo_channels
        for(ushort j = 0; j < command_args.size(); j++){
            found = false;
            for(map<string, vector<User>>::iterator it = listo_channels.begin(); it != listo_channels.end(); it++) {
                for (ushort i = 0; i < it->second.size(); i++) {
                    if ((it->second)[i].getName() == command_args[j] && !found) {
                        ison += command_args[j] + " is online.\n";
                        found = true;
                    }
                }
            }
        }
        return ison;
    }
    else {
        return "/ISON: Please specify one or more users.\n";   
    }
}


// Join the channel
string JOIN(User &user, map<string, vector<User>> &listo_channels) {
    if (command_args.size() > 0) {

        // Create new channel if it doesn't exist
        if (listo_channels[command_args[0]].empty()) cout << "New channel @" << command_args[0] << " created by " << user.getName() << "." << endl;
        user.setChan(command_args[0]);

        // User is not in channel, send join message
        if (!userInChannel(user, listo_channels)) {
            listo_channels[user.getChan()].push_back(user);
            sendToAll(user, listo_channels, user.getName() + " has joined the @" + user.getChan() + " channel!\n");
            return "You have now joined the @" + user.getChan() + " channel!\n";
        }

        // User is already in channel, send switch message
        else {
            cout << user.getName() << " switched back to @" << user.getChan() << "." << endl;
            return "Switched back to @" + user.getChan() + ".\n";
        }

    }
    else {
        return "/JOIN: Please specify a channel name.\n";
    }
}


// Send invite request to channel
string KNOCK(User &user, map<string, vector<User>> &listo_channels) {

    if (command_args.size() < 1) {
        return "/KNOCK: Please specify a channel and an optional message if desired.\n";
    }

    bool channel_exists = false;
    string channel = command_args[0];

    // Check if channel exists
    for(map<string, vector<User>>::iterator it = listo_channels.begin(); it != listo_channels.end(); it++)
        if ((it->first) == channel) channel_exists = true;
    if (!channel_exists) {
        return "/KNOCK: Channel " + channel + " does not exist. You can create it by running the command /JOIN " + channel + ".\n";
    }

    string knock = "";

    // Get the message if specified
    if (command_args.size() > 1) {
        knock += "[" + user.getName() + "] ";
        for(ushort i = 1; i < command_args.size(); i++) knock += command_args[i] + ' ';
    }

    // Send invite message to everyone in channel
    for (ushort i = 0; i < listo_channels[channel].size(); i++) {
        listo_channels[channel][i].sendString(user.getName() + " has requested to join @" + channel + "!\n");
        if (knock != "") listo_channels[channel][i].sendString(knock + "\n");
    }

    return "Sent invite request to channel @" + channel + ".\n";
}


// Remove user from the channel
string KICK(User &user, map<string, vector<User>> &listo_channels) {

    // Check for correct number of arguments
    if (user.getLevel() != "user") {
        if (command_args.size() >= 2) {
            string kick = "";

            // Get message if specified
            if (command_args.size() > 2) {
                kick += "[" + user.getName() + "] ";
                for(ushort i = 2; i < command_args.size(); i++) kick += command_args[i] + ' ';
            }

            bool channel_exists = false;
            string username = command_args[0];
            string channel = command_args[1];

            //  @General
            if (channel == "general") {
                return "/KICK: Cannot remove " + username + " from @general. To ban " + username + " enter the command /KILL " + username + ".\n";
            }

            // Check if the channel exists
            for(map<string, vector<User>>::iterator it = listo_channels.begin(); it != listo_channels.end(); it++)
                if ((it->first) == channel) channel_exists = true;
            if (!channel_exists) {
                return "/KICK: Channel " + channel + " does not exist. You can create it by running the command /JOIN " + channel + ".\n";
            }

            // Search for user and send message
            for (ushort i = 0; i < listo_channels[channel].size(); i++) {
                if (listo_channels[channel][i].getName() == username) {
                    if (kick != "") listo_channels[channel][i].sendString(kick + "\n");
                    listo_channels[channel][i].sendString("@" + channel + "\n");
                    listo_channels[channel][i].setChan("general");
                    listo_channels[channel].erase(listo_channels[channel].begin() + i);
                    sendToAllExcept(user, listo_channels, username + " was removed from channel @" + channel + ".\n", username);
                    return username + " successfully removed from channel @" + channel + ".\n";
                }
            }

            // If the user was not found
            return "/KICK: User " + username + " was not found in channel @" + channel + ".\n";
        }
        else {
            return "/KICK: Please specify a user and a channel.\n";
        }
    }
    else {
        return "/KICK: You do not have the required privileges to run this command!\n";
    }
}


// Remove a user from the network
string KILL(User &user, map<string, vector<User>> &listo_channels) {

    // Check if user has required permissions
    if (user.getLevel() == "admin" || user.getLevel() == "sysop") { 
        if (command_args.size() > 0) {
            string username = command_args[0];
            string kill = "";

            // Get message if specified
            if (command_args.size() > 1) {
                kill += "[" + user.getName() + "] ";
                for(ushort i = 1; i < command_args.size(); i++) kill += command_args[i] + ' ';
            }
            
            // Search for user and kill them
            for(map<string, vector<User>>::iterator it = listo_channels.begin(); it != listo_channels.end(); it++) {
                for (ushort i = 0; i < it->second.size(); i++) {
                    if ((it->second)[i].getName() == username) {
                        if (kill != "") (it->second)[i].sendString(kill + "\n");
                        (it->second)[i].sendString("You have been removed from the server by " + user.getName() + "!\n");
                        // (it->second)[i].sendString("/QUIT\n"); <- shuts down server
                        cout << username << " was removed from the chat by " << user.getName() << "." << endl;
                        return "User " + username + " was removed from the chat!\n";
                    }
                }
            }
            return "/KILL: User " + username + " was not found.\n";
        }
        else {
            return "/KILL: Please specify a user.\n";
        }
    }
    else {
        return "/KILL: You do not have the required privileges to run this command!\n";
    }
}

// List listo_channels on the server
string LIST(map<string, vector<User>> &listo_channels) {
    string list = "listo_channels:\n";
    for(map<string, vector<User>>::const_iterator it = listo_channels.begin(); it != listo_channels.end(); it++)
        list += "  " + it->first + "\n";
    return list + "\n";
}

// Changes username
string NICK(User &user, map<string, vector<User>> &listo_channels){

    // Display current username
    if (command_args.size() == 0) {
        return "Your username is " + user.getName() + ".\n";
    }

    // Change username
    else if (command_args.size() == 1){
        string oldUsername = user.getName();
        string newUsername = command_args[0];

        // Check that username doesn't exist
        for(map<string, vector<User>>::iterator it = listo_channels.begin(); it != listo_channels.end(); it++) {
            for (ushort i = 0; i < it->second.size(); i++) {
                if ((it->second)[i].getName() == newUsername)
                    return "/NICK: The username " + newUsername + " is already taken.\n";
            }
        }

        // Change username
        user.setUsername(newUsername);
        user.sendString("^" + user.getName() + "\n");

        // Replace old username with new username in all listo_channels
        for(map<string, vector<User>>::iterator it = listo_channels.begin(); it != listo_channels.end(); it++) {
            for (ushort i = 0; i < it->second.size(); i++) {
                if ((it->second)[i].getName() == oldUsername) {
                    (it->second).erase((it->second).begin() + i);
                    (it->second).push_back(user);
                }
            }
        }

        // Send notification
        sendToAll(user, listo_channels, oldUsername + " changed their username to " + newUsername + ".\n");
        return "Changed username to " + newUsername + ".\n";
    } 

    else {
        return "/NICK: Your username can only be one word.\n";
    }
}


// Send notice to user
string NOTICE(User &user, map<string, vector<User>> &listo_channels) {

    // Check for correct number of arguments
    if (command_args.size() > 1) {
        bool userFound = false;
        string username = command_args[0];
        string notice = "[NOTICE:" + user.getName() + "] ";
        for(ushort i = 1; i < command_args.size(); i++) notice += command_args[i] + ' ';

        // Search for user and send message
        for(map<string, vector<User>>::iterator it = listo_channels.begin(); it != listo_channels.end(); it++) {
            for (ushort i = 0; i < it->second.size(); i++) {
                if ((it->second)[i].getName() == username && !userFound) {
                    (it->second)[i].sendString(notice + "\n");
                    userFound = true;
                }
            }
        }

        // User was not found
        if (!userFound) {
            return "/NOTICE: User " + command_args[0] + " was not found.\n";
        }
        else {
            return "Notice sent to " + username + ".\n";
        }
    }
    else {
        return "/NOTICE: Please specify a target user and message.\n";
    }
}


// Checks if a user is an admin/channelop/sysop
string OPER(map<string, vector<User>> &listo_channels){
    if (command_args.size() > 0){
        string username = command_args[0];
        bool userFound = false;

        // Search through listo_channels
        for(map<string, vector<User>>::iterator it = listo_channels.begin(); it != listo_channels.end(); it++) {
            for (ushort i = 0; i < it->second.size(); i++) {
                if ((it->second)[i].getName() == username) {
                    userFound = true;
                    if ((it->second)[i].getLevel() != "user") {
                        return username + " has " + (it->second)[i].getLevel() + " privileges.\n";
                    }
                }
            }
        }
        if (!userFound) {
            return "/OPER: User " + username + " was not found.\n";
        }
        else {
            return "User " + username + " has no special privileges.\n";
        }
    }
    else {
        return "/OPER: Please specify a single user to check operator privileges.\n";
    }
}


// Returns pong to the client
string PING(){
    return "PONG\n";
}


// Returns ping to the client
string PONG(){
    return "PING\n";
}


// Send private message to user
string PRIVMSG(User &user, map<string, vector<User>> &listo_channels) {

    // Check for correct number of arguments
    if (command_args.size() > 1) {
        bool userFound = false;
        string u = command_args[0];
        string prvmsg = "[PRIVMSG:" + user.getName() + "] ";
        for(ushort i = 1; i < command_args.size(); i++) prvmsg += command_args[i] + ' ';

        // Search for user and send the message
        for(map<string, vector<User>>::iterator it = listo_channels.begin(); it != listo_channels.end(); it++) {
            for (ushort i = 0; i < it->second.size(); i++) {
                if ((it->second)[i].getName() == u) {
                    (it->second)[i].sendString(prvmsg + "\n");
                    userFound = true;
                }
            }
        }

        // User was not found
        if (!userFound) {
            return "/PRIVMSG: User " + u + " was not found.\n";
        }
        else {
            return "Private message sent to " + u + ".\n";
        }
    }
    else {
        return "/PRIVMSG: Please specify a target user and message.\n";
    }
}


// Disconnects the client from the server
string QUIT(User &user, map<string, vector<User>> &listo_channels) {

    // Print the exiting message if specified
    if (command_args.size() > 0) {
        string goodbye = "[@" + user.getChan() + ":" + user.getName() + "] ";
        for(ushort i = 0; i < command_args.size(); i++) goodbye += command_args[i] + ' ';
        sendToAll(user, listo_channels, goodbye + "\n");
    }

    // Disconnect client
    user.sendString("/QUIT\n");
    sendToAll(user, listo_channels, user.getName() + " has left the chat.\n");
    user.disconnect();
    return "/QUIT\n";
}


// Print the server rules
string RULES(){
    string rules = "The only rules are as follows:\n1. No hate speech, racism, sexism, any other ism-like speech\n1. Have fun! :)";
    return rules;
}


// Sets username just like the nick command
string SETNAME(User &user, map<string, vector<User>> &listo_channels){
    // Display current username
    if (command_args.size() == 0) {
        return "Your username is " + user.getName() + ". /SETNAME newName to change it.\n";
    }

    // Changes username
    else if (command_args.size() == 1){
        string oldUsername = user.getName();
        string newUsername = command_args[0];

        // Checks that username doesn't exist
        for(map<string, vector<User>>::iterator it = listo_channels.begin(); it != listo_channels.end(); it++) {
            for (ushort i = 0; i < it->second.size(); i++) {
                if ((it->second)[i].getName() == newUsername)
                    return "/SETNAME: The username " + newUsername + " is already taken.\n";
            }
        }

        // Changes username
        user.setUsername(newUsername);
        user.sendString("^" + user.getName() + "\n");

        // Replace old username with new username in all listo_channels
        for(map<string, vector<User>>::iterator it = listo_channels.begin(); it != listo_channels.end(); it++) {
            for (ushort i = 0; i < it->second.size(); i++) {
                if ((it->second)[i].getName() == oldUsername) {
                    (it->second).erase((it->second).begin() + i);
                    (it->second).push_back(user);
                }
            }
        }

        // Send notification
        sendToAll(user, listo_channels, oldUsername + " changed their username to " + newUsername + ".\n");
        return "Changed username to " + newUsername + ".\n";
    } 

    else {
        return "/SETNAME: Your username can only be one word.\n";
    }
}

// Gets the current server time
string TIME(){
    if (command_args.size() < 1){
        time_t t = time(0);
        struct tm  tt;
        char       time[80];
        tt = *localtime(&t);
        strftime(time, sizeof(time), "%Y-%m-%d.%X\n", &tt);

        return time;
    }
    else {
        return "/TIME: please specify no arguments to see current server time.\n";
    }
}


// Returns the current username to the client
string USER(User &user){
    // Display current username
    if (command_args.size() == 0) {
        return "Your username is " + user.getName() + ".\n";
    }
    else {
        return "Cannot execute /USER with arguments, use /SETNAME newName to change username.\n";
    }
}


// Returns the current host to the client
string USERHOST(User &user){
    // Display current username
    if (command_args.size() == 0) {
        return "Your hostname is " + user.getHostname() + ".\n";
    }
    else {
        return "Cannot execute /USERHOST with arguments.\n";
    }
}


// Returns current User IP address
string USERIP(User &user){
    // Display current username
    if (command_args.size() == 0) {
        return "Your IP Address is " + user.getHostname() + ".\n";
    }
    else {
        return "Cannot execute /USERIP with arguments.\n";
    }
}


// Returns all online users
string USERS(User &user, map<string, vector<User>> &listo_channels){
    if (command_args.size() > 0){
        return "Cannot execute /USERS with arguments, please try again without arguments.\n";
    }
    else {
        string all = "";
        map<string, int> u;

        // Go through all users in every channel and add to map (no duplicate entries)
        for(map<string, vector<User>>::iterator it = listo_channels.begin(); it != listo_channels.end(); it++) {
            for (ushort i = 0; i < it->second.size(); i++) {
                u[listo_channels[user.getChan()][i].getName()] += 1;
            }
        }

        // Add users to string
        for(map<string, int>::iterator it2 = u.begin(); it2 != u.end(); it2++) 
            all += (it2->first) + ", ";

        return all + "\n";
    }
}


// Returns the server version
string VERSION() {
    string version = "Server Version 1.0\n";
    return version;
}

// Returns your username
string WHO(User &user){
    if (command_args.size() == 0) {
        return "You are " + user.getName() + ".\n";
    }
    else {
        return "Can't run /WHO with arguments, use /SETNAME [newName] to change username.\n";
    }
}


// Returns the username and hostname of a user
string WHOIS(map<string, vector<User>> &listo_channels){
    if (command_args.size() > 0){
        string username = command_args[0];
        string hostname = "";
        bool userFound = false;
        for(map<string, vector<User>>::iterator it = listo_channels.begin(); it != listo_channels.end(); it++) {
            for (ushort i = 0; i < it->second.size(); i++) {
                if ((it->second)[i].getName() == username) {
                    userFound = true;
                    hostname = (it->second)[i].getHostname();
                }
            }
        }
        if (!userFound) { return username + " was not found, they are offline.\n"; }
        else {
            return username + " is online on " + hostname + "\n";
        }
    }
    else {
        return "Please run WHOIS with one argument, a username, to learn if they are online and what hostname they have.\n";
    }
}

// Checks to see if a user is already in the channel
bool userInChannel(User &user, map<string, vector<User>> &listo_channels) {
    for (ushort i = 0; i < listo_channels[user.getChan()].size(); i++)
        if (listo_channels[user.getChan()][i].getName() == user.getName()) {
            return true;
        }
    return false;
}


// Send message to everyone in channel and display on server
void sendToAll(User user, map<string, vector<User>> &listo_channels, string msg) {
    if (msg != "/QUIT\n") cout << msg;
    for (ushort i = 0; i < listo_channels[user.getChan()].size(); i++)
        if (listo_channels[user.getChan()][i].getName() != user.getName())
            listo_channels[user.getChan()][i].sendString(msg);
}


// Send message to everyone in channel except one user and display on server
void sendToAllExcept(User user, map<string, vector<User>> &listo_channels, string msg, string username) {
    cout << msg;
    for (ushort i = 0; i < listo_channels[user.getChan()].size(); i++)
        if (listo_channels[user.getChan()][i].getName() != user.getName() && listo_channels[user.getChan()][i].getName() != username)
            listo_channels[user.getChan()][i].sendString(msg);
}
