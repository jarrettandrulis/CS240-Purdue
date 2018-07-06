
const char * usage =
"                                                               \n"
"IRCServer:                                                   \n"
"                                                               \n"
"Simple server program used to communicate multiple users       \n"
"                                                               \n"
"To use it in one window type:                                  \n"
"                                                               \n"
"   IRCServer <port>                                          \n"
"                                                               \n"
"Where 1024 < port < 65536.                                     \n"
"                                                               \n"
"In another window type:                                        \n"
"                                                               \n"
"   telnet <host> <port>                                        \n"
"                                                               \n"
"where <host> is the name of the machine where talk-server      \n"
"is running. <port> is the port number you used when you run    \n"
"daytime-server.                                                \n"
"                                                               \n";

#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <map>

#include "IRCServer.h"

using namespace std;

int QueueLength = 5;

//test

int
IRCServer::open_server_socket(int port) {

	// Set the IP address and port for this server
	struct sockaddr_in serverIPAddress; 
	memset( &serverIPAddress, 0, sizeof(serverIPAddress) );
	serverIPAddress.sin_family = AF_INET;
	serverIPAddress.sin_addr.s_addr = INADDR_ANY;
	serverIPAddress.sin_port = htons((u_short) port);
  
	// Allocate a socket
	int masterSocket =  socket(PF_INET, SOCK_STREAM, 0);
	if ( masterSocket < 0) {
		perror("socket");
		exit( -1 );
	}

	// Set socket options to reuse port. Otherwise we will
	// have to wait about 2 minutes before reusing the sae port number
	int optval = 1; 
	int err = setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, 
			     (char *) &optval, sizeof( int ) );
	
	// Bind the socket to the IP address and port
	int error = bind( masterSocket,
			  (struct sockaddr *)&serverIPAddress,
			  sizeof(serverIPAddress) );
	if ( error ) {
		perror("bind");
		exit( -1 );
	}
	
	// Put socket in listening mode and set the 
	// size of the queue of unprocessed connections
	error = listen( masterSocket, QueueLength);
	if ( error ) {
		perror("listen");
		exit( -1 );
	}

	return masterSocket;
}

void
IRCServer::runServer(int port)
{
	int masterSocket = open_server_socket(port);

	initialize();
	
	while ( 1 ) {
		
		// Accept incoming connections
		struct sockaddr_in clientIPAddress;
		int alen = sizeof( clientIPAddress );
		int slaveSocket = accept( masterSocket,
					  (struct sockaddr *)&clientIPAddress,
					  (socklen_t*)&alen);
		
		if ( slaveSocket < 0 ) {
			perror( "accept" );
			exit( -1 );
		}
		
		// Process request.
		processRequest( slaveSocket );		
	}
}

int
main( int argc, char ** argv )
{
	// Print usage if not enough arguments
	if ( argc < 2 ) {
		fprintf( stderr, "%s", usage );
		exit( -1 );
	}
	
	// Get the port from the arguments
	int port = atoi( argv[1] );

	IRCServer ircServer;

	// It will never return
	ircServer.runServer(port);
	
}

//
// Commands:
//   Commands are started y the client.
//
//   Request: ADD-USER <USER> <PASSWD>\r\n
//   Answer: OK\r\n or DENIED\r\n
//
//   REQUEST: GET-ALL-USERS <USER> <PASSWD>\r\n
//   Answer: USER1\r\n
//            USER2\r\n
//            ...
//            \r\n
//
//   REQUEST: CREATE-ROOM <USER> <PASSWD> <ROOM>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: LIST-ROOMS <USER> <PASSWD>\r\n
//   Answer: room1\r\n
//           room2\r\n
//           ...
//           \r\n
//
//   Request: ENTER-ROOM <USER> <PASSWD> <ROOM>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: LEAVE-ROOM <USER> <PASSWD>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: SEND-MESSAGE <USER> <PASSWD> <MESSAGE> <ROOM>\n
//   Answer: OK\n or DENIED\n
//
//   Request: GET-MESSAGES <USER> <PASSWD> <LAST-MESSAGE-NUM> <ROOM>\r\n
//   Answer: MSGNUM1 USER1 MESSAGE1\r\n
//           MSGNUM2 USER2 MESSAGE2\r\n
//           MSGNUM3 USER2 MESSAGE2\r\n
//           ...\r\n
//           \r\n
//
//    REQUEST: GET-USERS-IN-ROOM <USER> <PASSWD> <ROOM>\r\n
//    Answer: USER1\r\n
//            USER2\r\n
//            ...
//            \r\n
//
std::vector<std::string> split(string str)
{
	string buffer;
	stringstream ss(str);
	vector<string> commands;
	while(ss >> buffer)
	{
		commands.push_back(buffer);
	}
}
void
IRCServer::processRequest( int fd )
{
	// Buffer used to store the comand received from the client
	const int MaxCommandLine = 1024;
	char commandLine[ MaxCommandLine + 1 ];
	int commandLineLength = 0;
	int n;
	
	// Currently character read
	unsigned char prevChar = 0;
	unsigned char newChar = 0;
	
	//
	// The client should send COMMAND-LINE\n
	// Read the name of the client character by character until a
	// \n is found.
	//

	// Read character by character until a \n is found or the command string is full.
	while ( commandLineLength < MaxCommandLine &&
		read( fd, &newChar, 1) > 0 ) {

		if (newChar == '\n' && prevChar == '\r') {
			break;
		}
		
		commandLine[ commandLineLength ] = newChar;
		commandLineLength++;

		prevChar = newChar;
	}
	
	// Add null character at the end of the string
	// Eliminate last \r
	commandLineLength--;
        commandLine[ commandLineLength ] = 0;
	
	printf("RECEIVED: %s\n", commandLine);
	printf("The commandLine has the following format:\n");
	printf("COMMAND <user> <password> <arguments>. See below.\n");
	printf("You need to separate the commandLine into those components\n");
	printf("For now, command, user, and password are hardwired.\n");

	const char * command = strtok(commandLine, " ");
	const char * user = strtok(NULL, " ");
	const char * password = strtok(NULL, " ");
	const char * arg1 = strtok(NULL, " ");
	const char * arg2 = strtok(NULL, "\0");

	printf("command=%s\n", command);
	printf("user=%s\n", user);
	printf( "password=%s\n", password );
	printf("arg1=%s\n", arg1);
	printf("arg2=%s\n", arg2);
	if (!strcmp(command, "ADD-USER")) {
		addUser(fd, user, password, arg1);
	}
	else if(checkPassword(fd,user,password))
	{
		if (!strcmp(command, "ENTER-ROOM")) {
			enterRoom(fd, user, password, arg1);
		}
		else if (!strcmp(command, "LEAVE-ROOM")) {
			leaveRoom(fd, user, password, arg1);
		}
		else if (!strcmp(command, "CREATE-ROOM")) {
			createRoom(fd, user, password, arg1);
		}
		else if (!strcmp(command, "LIST-ROOMS")) {
			listRooms(fd, user, password, arg1);
		}
		else if (!strcmp(command, "SEND-MESSAGE")) {
			sendMessage(fd, user, password, arg1, arg2);
		}
		else if (!strcmp(command, "GET-MESSAGES")) {
			getMessages(fd, user, password, arg1, arg2);
		}
		else if (!strcmp(command, "GET-USERS-IN-ROOM")) {
			getUsersInRoom(fd, user, password, arg1);
		}
		else if (!strcmp(command, "GET-ALL-USERS")) {
			getAllUsers(fd, user, password, arg1);
		}
		else {
			const char * msg =  "UNKNOWN COMMAND\r\n";
			write(fd, msg, strlen(msg));
		}
		
	}
	else if(!checkPassword(fd,user,password))
	{
		const char * msg = "ERROR (Wrong password)\r\n";
		write(fd, msg, strlen(msg));
	}


	// Send OK answer
	//const char * msg =  "OK\n";
	//write(fd, msg, strlen(msg));

	close(fd);	
}

void
IRCServer::initialize()
{
	// Open password file
	FILE * f = fopen(PASSWORD_FILE,"r+");
    char * line1 = NULL;
	char * line2 = NULL;
	users["testuser1"] = "test";
	users["testuser2"] = "test";
    size_t len = 0;
    ssize_t read;
	// Initialize users in room

	// Initalize message list

}
void 
IRCServer::createRoom(int fd, const char * user, const char * password, const char * args)
{
		// Here add a new user. For now always return OK.
	const char * msg;
	if ( loggedInUsers.find(user) == loggedInUsers.end() ) {
		msg =  "DENIED\r\n";
		write(fd, msg, strlen(msg));
	} else {
		
	}
	if ( rooms.find(args) == rooms.end() ) {
		room r;
		r.name = args;
		r.userCount = 0;
		r.numMessages = 0;
		map<string,string> m;
		r.users = m;
		rooms[args] = r;
		cout << rooms.size() << endl;
		msg =  "OK\r\n";
	} else {
		msg =  "DENIED\r\n";
		write(fd, msg, strlen(msg));
		return;
	}
	write(fd, msg, strlen(msg));
	return;	
}
bool
IRCServer::checkPassword(int fd, const char * user, const char * password) {
	const char * msg;
	if((loggedInUsers.find(user) == loggedInUsers.end()) || loggedInUsers[user] != password)
	{
		return false;
	}
	return true;
}

void
IRCServer::addUser(int fd, const char * user, const char * password, const char * args)
{
	// Here add a new user. For now always return OK.
	const char * msg;
	if ( loggedInUsers.find(user) == loggedInUsers.end()&&(users.find(user) == users.end() || users[user] == password )){
		loggedInUsers[user] = password;
		cout << loggedInUsers.size() << endl;
		msg =  "OK\r\n";
	} else {
		msg =  "DENIED\r\n";
	}
	write(fd, msg, strlen(msg));

	return;		
}

void
IRCServer::enterRoom(int fd, const char * user, const char * password, const char * args)
{
	const char * msg;
	if ( loggedInUsers.find(user) == loggedInUsers.end() ) {
		msg =  "DENIED\r\n";
		write(fd, msg, strlen(msg));
		return;
	} else {
		msg =  "OK\r\n";
	}
	if ( rooms.find(args) == rooms.end() ) {
		msg =  "ERROR (No room)\r\n";
		write(fd, msg, strlen(msg));
		return;
	}
	rooms[args].users[user] = password;
	write(fd, msg, strlen(msg));
}

void
IRCServer::leaveRoom(int fd, const char * user, const char * password, const char * args)
{
	const char * msg;
	if ( loggedInUsers.find(user) == loggedInUsers.end() ) {
		msg =  "DENIED\r\n";
	} else {
		msg =  "OK\r\n";
	}
	if ( rooms.find(args) == rooms.end() ) {
		msg =  "DENIED\r\n";
		write(fd, msg, strlen(msg));
		return;
	}
	if ( rooms[args].users.find(user) == rooms[args].users.end() ) {
		msg =  "ERROR (No user in room)\r\n";
		write(fd, msg, strlen(msg));
		return;
	}
	rooms[args].users.erase(user);
	msg =  "OK\r\n";
	write(fd, msg, strlen(msg));
}

void
IRCServer::sendMessage(int fd, const char * user, const char * password, const char * arg1, const char * arg2)
{
	const char * msg;
	if ( loggedInUsers.find(user) == loggedInUsers.end() ) {
		msg =  "DENIED\r\n";
	} else {
		msg =  "OK\r\n";
	}
	if ( rooms.find(arg1) == rooms.end() ) {
		msg =  "DENIED\r\n";
		write(fd, msg, strlen(msg));
		return;
	}
	if ( rooms[arg1].users.find(user) == rooms[arg1].users.end() ) {
		msg =  "ERROR (user not in room)\r\n";
		write(fd, msg, strlen(msg));
		return;
	}
	string message = "";
	char str[20];
	sprintf(str,"%d",rooms[arg1].numMessages);
	message += str;
	message += + " ";
	message += user;
	message += " ";
	message += arg2;
	rooms[arg1].messages[rooms[arg1].numMessages++] = message;
	write(fd, msg, strlen(msg));
}

void
IRCServer::getMessages(int fd, const char * user, const char * password, const char * arg1, const char * arg2)
{
	const char * msg;
	if ( loggedInUsers.find(user) == loggedInUsers.end() ) {
		msg =  "DENIED\r\n";
	} else {
		msg =  "OK\r\n";
	}
	if ( rooms[arg2].users.find(user) == rooms[arg2].users.end() ) {
		msg =  "ERROR (User not in room)\r\n";
		write(fd, msg, strlen(msg));
		return;
	} else {
		msg =  "OK\r\n";
	}
	string message = "";
	if(atoi(arg1) >= rooms[arg2].numMessages)
	{
		msg =  "NO-NEW-MESSAGES\r\n";
		write(fd, msg, strlen(msg));
		return;
	}
	for(int i = atoi(arg1)+1; i < rooms[arg2].numMessages; i++){
		message += rooms[arg2].messages[i];
		message += "\r\n";
	}
	message += "\r\n";
	write(fd, message.c_str(), message.length());
}
void
IRCServer::listRooms(int fd, const char * user, const char * password, const char * args)
{
	const char * msg;
	msg = "";
	if ( loggedInUsers.find(user) == loggedInUsers.end() ) {
		msg =  "DENIED\r\n";
	} else {
		map<string,room>::iterator it;
		string x = "";
		for(it = rooms.begin(); it != rooms.end(); it++){
			x += it->first + "\n";
		}
		msg = x.c_str();
	}
	write(fd, msg, strlen(msg));
}

void
IRCServer::getUsersInRoom(int fd, const char * user, const char * password, const char * args)
{
	const char * msg;
	if ( loggedInUsers.find(user) == loggedInUsers.end() ) {
		msg =  "DENIED\r\n";
	} else {
		msg =  "OK\r\n";
	}
	map<string, string>::iterator iter;
	string message = "";
	for(iter =rooms[args].users.begin(); iter!=rooms[args].users.end();iter++)
	{
		message+=iter->first;
		message+="\r\n";
	}
	message+="\r\n";
	write(fd, message.c_str(), message.length());
}

void
IRCServer::getAllUsers(int fd, const char * user, const char * password,const  char * args)
{
	const char * msg;
	if ( loggedInUsers.find(user) == loggedInUsers.end() ) {
		msg =  "DENIED\r\n";
	} else {
		msg =  "OK\r\n";
	}
    map<string, string>::iterator iter;
	string message = "";
	for(iter =loggedInUsers.begin(); iter!=loggedInUsers.end();iter++)
	{
		message+=iter->first;
		message+="\r\n";
	}
	message+="\r\n";
	write(fd, message.c_str(), message.length());
}

