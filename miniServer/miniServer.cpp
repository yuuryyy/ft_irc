/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:35:10 by hmoukit           #+#    #+#             */
/*   Updated: 2025/06/21 14:19:58 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniServer.hpp"

int miniServer::serverSocket()
{
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd < 0)
        throw std::runtime_error("ERROR: Problem in socket()");
    // retrieves the current flags
    int flag = fcntl(socketFd, F_GETFL, 0);
    if (flag < 0)
        throw std::runtime_error("ERROR: Problem in fcntl()");
    // preserving existing behavior and just enabling non-blocking mode additionally 
    int check = fcntl(socketFd, F_SETFL, flag | O_NONBLOCK);
    if (check < 0)
        throw std::runtime_error("ERROR: Problem in fcntl()");
    // when a server stops and restarts it might be consider in use by the os 
    //so we use SO_REUSEADDR  to say Let me bind this socket even if a previous
    //connection on the same address is still in the TIME_WAIT state 
    int option = 1;
    if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) < 0)
        throw std::runtime_error("ERROR: Problem in setsockopt()");
    sockaddr_in address;
    // bind to all network interface on this machine
    address.sin_addr.s_addr = INADDR_ANY;
    // sets the address family to IPv4
    address.sin_family = AF_INET;
    // converts the host byte order to network byte order (big-endian)
    //which is required by the sockets API
    address.sin_port = htons(port);
    //bind so the socket is responsible for handling incoming connections to this IP and port
    if (bind(socketFd, (struct sockaddr *)&address, sizeof(address)) < 0)
        throw std::runtime_error("ERROR: Problem in bind()");
    // SOMAXCONN: maximum connection queue size allowed by the system
    // we listen for incoming TCP connections on this socket
    if (listen(socketFd, SOMAXCONN) < 0)
        throw std::runtime_error("ERROR: Problem in listen()");
    // preparing to use poll syscall
    pollfd pfd;
    pfd.fd = socketFd;
    pfd.events = POLLIN;
    fdsVec.push_back(pfd);
    return (socketFd);
}

void miniServer::handleNewConnections(int socketFd){
    sockaddr_in clientAdress;
    socklen_t len = sizeof(clientAdress);
    int new_socket = accept(socketFd, (struct sockaddr *) &clientAdress, &len);
    if (new_socket < 0){
        return ;
    }
    std::cout << "client connected" << std::endl;
    int flags = fcntl(new_socket, F_GETFL, 0);
    fcntl(new_socket, F_SETFL, flags | O_NONBLOCK);
    pollfd new_fd;
    new_fd.fd = new_socket;
    new_fd.events = POLLIN;
    fdsVec.push_back(new_fd);
    /*
    Client client;
    client.fd = new_fd.fd;
    */
    // client[new_fd.fd] = Client();
}

// void miniServer::handleClientData(int fd)
// {
//     currentClient = fd;
//     std::vector<std::string>& cmd = client[fd].getCmds();
//     for(size_t i=0; i< cmd.size(); i++){
//         parse_cmd(cmd[i]);
//     }
//     cmd.clear();
// }

int miniServer::runningServer(int socketFd)
{
    constexpr size_t BUFFER_SIZE = 1024;
    while (true) {
        int monitor = poll(fdsVec.data(), fdsVec.size(), -1);
        if (monitor < 0) {
            if (errno == EINTR)
                continue;
            throw std::runtime_error("Error : Failed poll");
        }

        // Iterate in reverse to safely erase elements
        for (int i = fdsVec.size() - 1; i >= 0; i--) {
            short revents = fdsVec[i].revents;
            if (revents & (POLLHUP | POLLERR | POLLNVAL)) {
                close(fdsVec[i].fd);
                std::cout << "Client " << fdsVec[i].fd << " disconnected (error/hangup)" << std::endl;
                // client.erase(fdsVec[i].fd);
                fdsVec.erase(fdsVec.begin() + i);
                continue;
            }

            if (revents & POLLIN) {
                if (fdsVec[i].fd == socketFd) {
                    handleNewConnections(socketFd);
                } else {
                    char buffer[BUFFER_SIZE + 1] = {0};
                    int bytes = recv(fdsVec[i].fd, buffer, BUFFER_SIZE, 0);
                    if (bytes <= 0) {
                        close(fdsVec[i].fd);
                        std::cout << "Client " << fdsVec[i].fd << " disconnected" << std::endl;
                        // client.erase(fdsVec[i].fd);
                        fdsVec.erase(fdsVec.begin() + i);
                    } else {
                        buffer[bytes] = '\0';
                        // client[fdsVec[i].fd].AddBuffer(buffer);
                        // client[fdsVec[i].fd].extract_cmds();
                        // handle_client_data(fdsVec[i].fd);
                    }
                }
            }
        }
    }
}

