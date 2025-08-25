#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include <string>
#include "../client/Client.hpp"
#include "iostream"

class Channel {
    private:
        std::string Name;
        std::string Password;
        std::string _modes;
        bool paswrd;
        std::vector<Client> members;
        std::vector<Client> Ops;
        // uint                _capacityLimit;
        
    public:
        Channel();
        ~Channel();
        // Channel(std::string name);
        std::string& GetName(void);
        void SetName(std::string& name);
        std::string& GetPassword(void);
        void SetPassword(std::string& password);
        bool GetBoolPswd(void);
        void SitBoolPswd(bool is);
        std::vector<Client>& GetMembers(void);
        std::vector<Client>& GetOps(void);
        //get username of ops
};

#endif