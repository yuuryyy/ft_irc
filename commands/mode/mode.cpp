/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rambeau <rambeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 01:55:22 by ychagri           #+#    #+#             */
/*   Updated: 2025/09/01 12:00:26 by rambeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


Channel*
Server::channelExist( const std::string &name )
{
    it  itt = this->_channel.find(name);

    if (itt != this->_channel.end())
        return &itt->second;
    return NULL;
}

void
Server::MODE( void )
{
    size_t  size = this->_line.size();
    
    if ( size < 2)
        return (this->sendReply(std::string(ERR_NEEDMOREPARAMS(this->_client[this->_currentClient].getnick(), "MODE"))));

    Channel *channel = channelExist(this->_line[1]);
    
    if (channel)
    {
        if (size == 2)
        {
            sendReply(std::string(RPL_CHANNELMODEIS(this->_client[this->_currentClient].getnick(),
                        channel->GetName(),
                        channel->getModes())));
            

            std::string time = std::to_string(channel->getTime());

            sendReply(std::string(RPL_CREATIONTIME(this->_client[this->_currentClient].getnick(),
                        channel->GetName(),
                        time)));
            return;
        }

        
    }
    //error

}