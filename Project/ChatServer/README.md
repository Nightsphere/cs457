# Chat server and client.
  - Created by Josh Keahey
  - This program is a chat server and client that create a chat program with users, channels, and 
	many other different commands that can be used. It is inspired by the IRC protocol.

### Compiling the program.
  - To compile the program, type 'make'

### Starting the server.
  - To start the server, type 'server'

### To join as client.
To join the server as a client, type "client -h 127.0.0.1 -u <username> -p 2000"
  - -h: host (127.0.0.1)
  - -u: user
  - -p: port number (the default is 2000, you can use any port you want, just be careful the one you pick is free)
  - All 3 options above must be used to determine what host to connect to, the user's nickname, and the port to be used

### What to do after you've joined.
After you've joined the server as a client, you can: 
  1. Start typing to send messages to other clients in the chat
  2. Type '/help' to see a list of available commands and each ones arguments if needed

### List of Commands
  1. '/DIE' - Shuts down the server if the client has admin privileges
  2. '/HELP' - Displays a list of available commands
  3. '/INFO' - Diplays information about the creator of the program
  4. '/INVITE [username] [channel]' - Sends an invitation to [username] requesting that they join the [channel]
  5. '/ISON [username]' - Displays whether [username] is online
  6. '/JOIN [channel]' - Allows you to join [channel] 
  7. '/KICK [username] [reason]' - Removes [username] from the current channel and shows the optional reason for the kick
  8. '/KILL [username]' - Removes [username] from the chat if client has admin or sysop privileges
  9. '/KNOCK [channel] [message]' - Knocks on a channel by sending an optional message or a default message to all users 
  in the current channel
  10. '/LIST' - Displays a list of all currently available channels
  11. '/NICK [newNickname]' - Changes your username and checks that it's not already taken or tells you what it already 
  is if run with no argument
  12. '/NOTICE [username] [message]' - Sends a private message to [username]
  13. '/OPER [username]' - Will check if username is online and returns what kind of privelege they have, which could be 
  user, admin, sysop, or channelop
  14. '/PING' - Responds with 'PONG'
  15. '/PONG' - Responds with 'PING'
  16. '/PRIVMSG [username] [message]' - Sends a private message to [username]
  17. '/QUIT [message]' - Ends connection and tells everyone in the current channel you left, displaying the optional 
  message
  18. '/RULES' - Shows the server rules
  19. '/SETNAME [newUsername]' - Same as command [11]
  20. '/TIME' - Shows the current time
  21. '/USER' - Displays the client's username
  22. '/USERHOST' - Displays the hostname (default is 2000)
  23. '/USERS' - Displays everyone currently online
  24. '/USERIP' - Displays your IP address
  25. '/VERSION' - Displays the version of the chat server
  26. '/WHO' - Shows your username.
  27. '/WHOIS' - Displays your username and the hostname of the server
  
