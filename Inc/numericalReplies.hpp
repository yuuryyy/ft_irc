/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericalReplies.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rambeau <rambeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 01:17:18 by ychagri           #+#    #+#             */
/*   Updated: 2025/09/01 11:59:54 by rambeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

#define SERVERNAME  "localhost"

#define ERR_NEEDMOREPARAMS(n, c)    ":"  SERVERNAME " 461 " + n + " " + c + " :Not enough parameters\r\n"
#define RPL_CHANNELMODEIS(n, c, s)  ":"  SERVERNAME " 324 " + n + " " + c + " " + s + "\r\n"
#define RPL_CREATIONTIME(n,c,t)     ":"  SERVERNAME " 324 " + n + " " + c + " " + t + "\r\n"


// void sendServerRpl(int const client_fd, std::string client_buffer); //This function takes a client file descriptor and a formatted message buffer, then sends the message to the appropriate client.