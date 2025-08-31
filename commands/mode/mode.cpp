/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 01:55:22 by ychagri           #+#    #+#             */
/*   Updated: 2025/08/31 00:50:42 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


bool
Server::channelExist( const std::string &name ) const
{
    std::map<std::string , Channel>::const_iterator it = this->_channel.find(name);

    return (it != this->_channel.end()) ? true : false;
}


void
Server::MODE( void )
{
    if (this->_line.size() < 2)
        return (this->sendErr(makeReply(ERR_NEEDMOREPARAMS), "MODE"));
    
    // else if (this->)

}