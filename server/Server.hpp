#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <vector>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <map>
#include "../client/Client.hpp"
#include <fcntl.h>
#include <sstream>
#include <stdexcept>
#include "../channel/Channel.hpp"
#include <algorithm>

enum Commands {
    PASS_cmd,
    NICK_cmd,
    USER_cmd,
    JOIN_cmd,
    PART_cmd,
    MODE_cmd,
    TOPIC_cmd,
    KICK_cmd,
    INVITE_cmd,
    UNKNOWN_cmd
};


class Server {
    private:
        int port;
        std::string password;
        int Socket_fd;
        std::map<int, Client> client;
        int currentClient;
        std::vector<Channel> channel;
        std::vector<pollfd> poll_fds;
        std::vector<std::string> line;
        std::map<std::string, Commands> cmd;

    public:
        Server(int port , std::string password);
        ~Server();
        int start(void);
        int server_socket(void);
        int running_server(int Socket_fd);
        void handle_new_connections(int Socket_fd);
        void handle_client_data(int fd);
        void parse_cmd(std::string cmd);
        void commands_handler(void);
        void initCmds(void);
        int GetCmds(void);
        void JOIN(void);
        int IsChannelExist(std::string ChanName);
        int split(std::vector<std::string> *channels, std::string& chan, char delimiter);
        int JoinParse(std::vector<std::string> *channels, std::vector<std::string> *keys);
};

#endif
