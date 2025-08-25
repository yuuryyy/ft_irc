#ifndef CLIENT_HPP
#define CLIENT_HPP

#include<string>
#include<map>
#include <vector>

class Client {
    private:
        std::string ip; // by inet_ntoa
        int port;  // by ntohs
        std::vector<std::string> cmds; //to store all cmds ends with /r/n
        bool registered;
        bool Op;
        std::string nick;
        std::string username;
        
        std::string Buffer;
        
    public:
        std::string& getBuffer(void);
        std::vector<std::string>& getCmds(void);
        void AddBuffer(const char *buf);
        void extract_cmds(void);
        std::string& GetUsername(void);
        void SitUsername(std::string user);

};

#endif