/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:35:18 by hmoukit           #+#    #+#             */
/*   Updated: 2025/06/21 14:19:53 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISERVER_HPP
# define MINISERVER_HPP

# include "../client/client.hpp"
# include <sys/socket.h>
# include <fcntl.h>
# include <netinet/in.h>
# include <poll.h>
# include <stdexcept>
# include <unistd.h>

class miniServer {
    private:
        int socketFd;
        int port;
        std::vector<pollfd> fdsVec;
    public:
        int serverSocket();
        void handleNewConnections(int socketFd);
        void handleClientData(int fd);
        int runningServer(int socketFd);
};

#endif