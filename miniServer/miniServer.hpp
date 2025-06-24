/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:35:18 by hmoukit           #+#    #+#             */
/*   Updated: 2025/06/25 00:46:59 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISERVER_HPP
# define MINISERVER_HPP

# include <iostream>
# include <sys/socket.h>
# include <fcntl.h>
# include <netinet/in.h>
# include <poll.h>
# include <stdexcept>
# include <unistd.h>
# include <errno.h>

class miniServer {
private:
    int socketFd;
    int port;

public:
    miniServer(int port);         // Constructor
    ~miniServer();                // Destructor
    void start();                 // Calls serverSocket + run loop
private:
    int serverSocket();           // Handles socket setup
    // void runServer(int fd); // Handles communication
    void handleClient(int clientFd);
};


#endif