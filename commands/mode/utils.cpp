/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rambeau <rambeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 08:45:48 by rambeau           #+#    #+#             */
/*   Updated: 2025/09/01 08:45:49 by rambeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

std::vector<std::string>    ftSplit(const std::string& str, const char del)
{
    std::vector<std::string>    tokens;
    std::string                 token;
    std::stringstream           ss(str);

    while (std::getline(ss, token, del))
    {
        if (!token.empty())
            tokens.push_back(token);
    }

    return tokens;
}

