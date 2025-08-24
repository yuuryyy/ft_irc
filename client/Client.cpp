#include "Client.hpp"

std::string& Client::getBuffer(void){
    return (this->Buffer);
}

std::vector<std::string>& Client::getCmds(void){
    return (cmds);
}

void Client::AddBuffer(const char *buf){
    this->Buffer += buf;
}

void Client::extract_cmds(void){
    size_t pos = 0;
    
    while ((pos = Buffer.find("\n")) != std::string::npos) { // WE WILL USE "\r\n" when we will use limechat
        std::string command = Buffer.substr(0, pos);
        
        if (!command.empty()) {
            cmds.push_back(command);
        }
        Buffer.erase(0, pos + 2);
    }
} // if the \r\n exactement in the end what find will return in buffer if it's empty

std::string& Client::GetUsername(void){
    return username;
}

void Client::SitUsername(std::string user){
    username = user;
}

bool Client::getregistered(void){
    return this->registered;
}

bool Client::getisPassed(void){
    return this->isPassed;
}

void Client::setisPassed(bool p){
    this->isPassed = p;
}

void Client::setregistered(bool r){
    this->registered = r;
}
