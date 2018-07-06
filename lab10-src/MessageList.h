
#ifndef IRC_SERVER
#define IRC_SERVER


class MessageList {
    std::string[100] messages;
    
    void addMessage(char * message);
    char * getMessage(int num);
};

#endif