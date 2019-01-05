CC = g++ -g
CFLAGS = -Wall -c
LFLAGS = -Wall -pthread
SOBJS = Socket.o ServerSocket.o Commands.o User.o
COBJS = Socket.o
INCLUDE = -I.


all: server client

server: $(SOBJS)
	$(CC) $(SOBJS) $(LFLAGS) $(INCLUDE) server.cpp -o server
	
client: $(COBJS)
	$(CC) $(COBJS) $(LFLAGS) $(INCLUDE) client.cpp -o client

Socket.o: Socket.cpp Socket.h
	$(CC) Socket.cpp $(INCLUDE) $(CFLAGS)

ServerSocket.o: ServerSocket.cpp ServerSocket.h
	$(CC) ServerSocket.cpp $(INCLUDE) $(CFLAGS)

Commands.o: Commands.cpp Commands.h
	$(CC) Commands.cpp $(INCLUDE) $(CFLAGS)
	
User.o: User.cpp User.h
	$(CC) User.cpp $(INCLUDE) $(CFLAGS)

clean:
	-rm *.o server client

