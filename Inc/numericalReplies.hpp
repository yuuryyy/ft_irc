/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericalReplies.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 01:17:18 by ychagri           #+#    #+#             */
/*   Updated: 2025/08/29 13:05:04 by hfiqar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

typedef struct s_replies
{
    std::string code;
    std::string msg;
	s_replies();
	s_replies(const std::string& c, const std::string& m);
} reply;

#define ERR_NEEDMOREPARAMS		reply("461", "Not enough parameters")
#define RPL_WELCOME				reply("001", "Welcome")
#define RPL_JOIN				reply("", "has joined a channel")
#define ERR_BANNEDFROMCHAN		reply("474", "cannot join because they are banned")
#define ERR_BADCHANNELKEY		reply("475", "provided an incorrect channel key")
#define ERR_NONICKNAMEGIVEN		reply("431", "No nickname provided")
#define ERR_ERRONEUSNICKNAME	reply("432", "ERR_ERRONEUSNICKNAME")
#define ERR_NICKNAMEINUSE		reply("433", "Nickname already in use")
#define ERR_ALREADYREGISTERED	reply("462", "User already registered")
#define ERR_PASSWDMISMATCH		reply("464", "Incorrect password")
#define ERR_INVITEONLYCHAN		reply("473", "invit only")
#define ERR_CHANNELISFULL		reply("471", " full channel")
