#ifndef CLIENT_HPP
#define CLIENT_HPP

#include<string>
#include<map>

class Client {
    private:
        std::string ip; // by inet_ntoa
        int port;  // by ntohs
        std::string Buffer;
        vector<std::string> cmds; //to store all cmds ends with /r/n
        
    public:
    void AddBuffer(const char *, int len);

};

#endif