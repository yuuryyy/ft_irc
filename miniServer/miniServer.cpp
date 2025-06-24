/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 02:35:10 by hmoukit           #+#    #+#             */
/*   Updated: 2025/06/25 00:51:22 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniServer.hpp"

miniServer::miniServer(int p) : socketFd(-1), port(p) {}

miniServer::~miniServer() {
    if (socketFd != -1)
        close(socketFd);
}


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
    return (socketFd);
}

void miniServer::handleClient(int clientFd) {
    std::cout << "Client connected: " << clientFd << std::endl;
    // Set up poll for this client
    pollfd clientPollFd;
    clientPollFd.fd = clientFd;
    clientPollFd.events = POLLIN;
    // Wait and handle communication with this client
    while (true)
    {
        int ret = poll(&clientPollFd, 1, -1);
        if (ret < 0)
            throw std::runtime_error("ERROR: poll() failed");
        if (clientPollFd.revents & POLLIN) {
            char buffer[1024] = {0};
            int bytes = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
            if (bytes <= 0)
            {
                std::cout << "Client disconnected." << std::endl;
                close(clientFd);
                break;
            }
            else
            {
                buffer[bytes] = '\0';
                std::cout << "Received: " << buffer << std::endl;
            }
        }
    }
    std::cout << "Finished handling client." << std::endl;
}

void miniServer::start() {
    socketFd = serverSocket();
    std::cout << "Server listening on port " << port << std::endl;
    // Use poll to wait for incoming connections
    pollfd serverPollFd;
    serverPollFd.fd = socketFd;
    serverPollFd.events = POLLIN;
    std::cout << "Waiting for a client to connect..." << std::endl;
    // Wait for a connection to be available
    int ret = poll(&serverPollFd, 1, -1); // -1 means wait indefinitely
    if (ret < 0)
        throw std::runtime_error("ERROR: poll() failed");
    if (serverPollFd.revents & POLLIN) {
        sockaddr_in clientAddr;
        socklen_t len = sizeof(clientAddr);
        int clientFd = accept(socketFd, (sockaddr*)&clientAddr, &len);
        if (clientFd < 0)
            throw std::runtime_error("ERROR: accept() failed");
            
        handleClient(clientFd);
    }
    std::cout << "Shutting down server" << std::endl;
}
