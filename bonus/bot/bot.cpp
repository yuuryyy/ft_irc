#include "Server.hpp"


const std::string
Server::botParser( void )
{
    std::string nick = this->_client[this->_currentClient].getnick();
    size_t  size = this->_line.size(); 
    std::string opt = this->_line[1];
    
    if (size < 2)
        return "";
    else if ((opt == "whois" ||  opt == "listusers") && size <= 2)
        return ERR_NEEDMOREPARAMS("*", "/BOT " + opt);
    if (opt == "help" || opt == "listcmds" || opt == "whois" ||  opt == "listusers")
        return opt;
    else
        return "";
}

void
Server::helpRpl(const std::string &option, const std::string reply[], int size)
{

    int         fd = this->_currentClient;
    std::string nick = this->_client[fd].getnick();

    sendReply(fd, RPL_HELPSTART(option));
    for(int i = 0; i < size; i++)
        sendReply(fd, RPL_HELPTXT( option, reply[i]));
    sendReply(fd, RPL_ENDOFHELP( option));
}

void
Server::help( void )
{
    std::string reply[] = {RPL_WHOIS, RPL_LISTUSERS, RPL_LISTCMDS};
    helpRpl("help",reply, 3);
} 

void
Server::whois(int fd)
{
    Client  *client = userExist(this->_line[2]);
    if (!client)
        return sendReply (fd, ERR_NOSUCHNICK("*", this->_line[2]));

    std::string reply[] =   {   W_USERNAME(client->GetUsername()),
                                W_NICKNAME(client->getnick()),
                                W_REALNAME(client->getrealname())
                            };
    
    helpRpl( "whois", reply, 3);
}

void
Server::listcmds( void )
{
    std::string reply[] = {
                "--------- Bonus bot commands -----------",
                RPL_CMD_HELP,
                RPL_WHOIS,
                RPL_LISTUSERS,
                RPL_LISTCMDS,
                "--------- mandatory commands -----------",
                RPL_CMD_PASS,
                RPL_CMD_NICK,
                RPL_CMD_USER,
                RPL_CMD_JOIN,
                RPL_CMD_MODE,
                RPL_MODE_I,
                RPL_MODE_T,
                RPL_MODE_K,
                RPL_MODE_L,
                RPL_MODE_O,
                RPL_CMD_TOPIC,
                RPL_CMD_KICK,
                RPL_CMD_PRIVMSG,
                };
    helpRpl( "listcmds", reply, 19);
}


void
Server::listusers(int fd, const std::string &nick)
{
    Channel *channel = this->channelExist(this->_line[2]);

    if (!channel)
        return sendReply(fd, ERR_NOSUCHCHANNEL(nick, this->_line[2]));

    std::map<std::string, Client>  members = channel->GetMembers();
    std::vector<std::string> names;
    for (std::map<std::string, Client>::iterator it = members.begin(); it != members.end(); ++it)
        names.push_back(it->first);

    helpRpl( "listusers", &names[0], channel->getMembersCount());

}

void
Server::BOT()
{
    int         fd = this->_currentClient;
    std::string nick = this->_client[fd].getnick();
    std::string user = this->_client[fd].GetUsername();
    if (nick != this->_botnick || user != this->_botusername)
    {
        std::cout<<"UNKNOWN : ";
        for(size_t i=0; i< _line.size(); i++)
            std::cout<< this->_line[i] << " ";
        std::cout<<std::endl;
        return ;
    }
    std::string option = this->botParser();

    if (option == "help")
        return this->help();
    else if (option == "whois")
        return this->whois(fd);
    else if (option == "listcmds")
        return this->listcmds();
    else if (option == "listusers")
        return this->listusers(fd, nick);
    else
        return sendReply(fd, option);
}