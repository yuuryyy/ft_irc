/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericalReplies.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychagri <ychagri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 01:17:18 by ychagri           #+#    #+#             */
/*   Updated: 2025/09/02 16:12:02 by ychagri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

#define SERVERNAME                      "localhost"

#define ERR_NEEDMOREPARAMS(nk, cm)      ":"  SERVERNAME " 461 " + nk + " " + cm + " :Not enough parameters\r\n"
#define RPL_CHANNELMODEIS(nk, ch, md)   ":"  SERVERNAME " 324 " + nk + " " + ch + " " + md + "\r\n"
#define RPL_CREATIONTIME(nk,ch,t)       ":"  SERVERNAME " 329 " + nk + " " + ch + " " + t + "\r\n"
#define ERR_NOSUCHCHANNEL(nk, ch)       ":"  SERVERNAME " 403 " + nk + " " + ch + " :No such channel\r\n"
#define ERR_UNKNOWNMODE(nk, md)         ":"  SERVERNAME " 472 " + nk + " " + md + " :is an unknown mode char to me\r\n"
#define ERR_CHANOPRIVSNEEDED(nk, ch)    ":"  SERVERNAME " 482 " + nk + " " + ch + " :You're not a channel operator\r\n"
#define ERR_NOTONCHANNEL(nk, ch)        ":"  SERVERNAME " 442 " + nk + " " + ch + " :You're not on that channel\r\n"

char    validModeString( const char &mode );

// void sendServerRpl(int const client_fd, std::string client_buffer); //This function takes a client file descriptor and a formatted message buffer, then sends the message to the appropriate client.