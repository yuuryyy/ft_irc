#include "Server.hpp"

int Server::JoinParse(std::vector<std::string> *channels, std::vector<std::string> *keys){
    if (line.size()<=1 || line.size()>3){
        std::cerr<<"Error join"<<std::endl;
        return 0;
    }
    if (!split(channels, line[1], ',')){
        std::cerr<<"specific replies"<<std::endl;
        return 0;
    }
    if (!line[2].empty() && !split(keys, line[2], ',')){
        std::cerr<<"specific replies"<<std::endl;
        return 0;
    }
    return 1;
}

int Server::split(std::vector<std::string> *channels, std::string& chans, char delimiter){
    std::stringstream line(chans);
    if (chans[chans.find_last_not_of(" \t") ] == delimiter){return 0;}
    std::string chan;
    while(std::getline(line, chan, delimiter)){
        chan.erase(0, chan.find_first_not_of(" \t"));
        chan.erase(chan.find_last_not_of(" \t") + 1);
        if (!chan.empty()){
            std::cout<<"test : "<<chans<<std::endl;
            (*channels).push_back(chan);
            chan.clear();
        }
        else{
            std::cerr<<"Error parsing in join"<<std::endl;
            chans.clear();
            return 0;
        }
    }
    chans.clear();
    return 1;
}

int Server::IsChannelExist(std::string ChanName){
    for(size_t i=0; i < channel.size(); i++){
        if (channel[i].GetName() == ChanName){
            return 1;
        }
    }
    return 0;
}

void Server::JOIN(void){
    std::vector<std::string> chans;
    std::vector<std::string> keys;
    JoinParse(&chans, &keys);
    for(size_t i=0; i< chans.size(); i++){
        std::cerr<<"channel : "<<chans[i]<<std::endl;
    }
    for(size_t i=0; i< keys.size(); i++){
        std::cerr<<"key : "<< keys[i]<<std::endl;
    }
}
