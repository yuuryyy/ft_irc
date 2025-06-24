/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:35:13 by hmoukit           #+#    #+#             */
/*   Updated: 2025/06/24 19:43:59 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniServer/miniServer.hpp"

int main()
{
    try
    {
        miniServer server(6667);
        server.start();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
