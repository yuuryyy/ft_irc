#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include "../client/Client.hpp"

class Channel {
    private:
        std::string Name;
        std::string Password;
        std::vector<Client> members;
        std::vector<Client> Ops;
        
    public:
        Channel();
        ~Channel();
        // Channel(std::string name);
        std::string& GetName(void);
        void SetName(std::string& name);
        std::string& GetPassword(void);
        void SetPassword(std::string& password);
        std::vector<Client>& GetMembers(void);
        std::vector<Client>& GetOps(void);
};

#endif