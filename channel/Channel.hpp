#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>

class Channel {
    private:
        bool op;
        std::string Name;
        
    public:
        Channel();
        ~Channel();
        Channel(std::string name);
        std::string& GetName(void);

};

#endif