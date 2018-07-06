
#ifndef IRC_SERVER
#define IRC_SERVER
#include <stdio.h>
#include <string>
#include <map>
#define PASSWORD_FILE "password.txt"
using namespace std;
class IRCServer {
	// Add any variables you need
	char * pwdFile;
	struct room{
		map<string,string> users;
		string messages[100];
		int numMessages;
		const char * name;
		int userCount;
		
	};
	map<string,string> users;
	map<string,string> loggedInUsers;
	map<string,room> rooms;
	

private:
	int open_server_socket(int port);

public:
	void initialize();
	bool checkPassword(int fd, const char * user, const char * password);
	void processRequest( int socket );
	void addUser(int fd, const char * user, const char * password, const char * args);
	void listRooms(int fd, const char * user, const char * password, const char * args);
	void enterRoom(int fd, const char * user, const char * password, const char * args);
	void createRoom(int fd, const char * user, const char * password, const char * args);
	void leaveRoom(int fd, const char * user, const char * password, const char * args);
	void sendMessage(int fd, const char * user, const char * password, const char * arg1, const char * arg2);
	void getMessages(int fd, const char * user, const char * password, const char * arg1, const char * arg2);
	void getUsersInRoom(int fd, const char * user, const char * password, const char * args);
	void getAllUsers(int fd, const char * user, const char * password, const char * args);
	void runServer(int port);
};
#endif
