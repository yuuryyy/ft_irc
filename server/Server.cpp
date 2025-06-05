#include "Server.hpp"

int Server::server_socket(){
    Socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    int flag = fcntl(Socket_fd, F_GETFL, 0);
    fcntl(Socket_fd, F_SETFL, flag | O_NONBLOCK);

    sockaddr_in serverAdress;
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_port = htons(6667); //check if this port is available
    serverAdress.sin_addr.s_addr = INADDR_ANY;

    if (bind(Socket_fd, (struct sockaddr *)&serverAdress, sizeof(serverAdress)) == -1){
        // perror("bind failed")
        close(Socket_fd);
        exit(1);
    }

    if (listen(Socket_fd, 15) == -1){
        // perror("listen failed")
        close(Socket_fd);
        exit(1);
    }
    //add the listening socket to the pollfd vector
    pollfd listen_fd;
    listen_fd.fd = Socket_fd;
    listen_fd.events = POLLIN;
    poll_fds.push_back(listen_fd);

    while(true){
        int monitor = poll(poll_fds.data(), poll_fds.size(), -1);
        if (monitor < 0){
            return(1);
        }
        for (size_t i=0 ; i < poll_fds.size() ; i++){
            if (poll_fds[i].revents & POLLIN){
                if (poll_fds[i].fd == Socket_fd){
                    sockaddr_in clientAdress;
                    socklen_t len = sizeof(clientAdress);
                    int new_socket = accept(Socket_fd, (struct sockaddr *) &clientAdress, &len);
                    int flags = fcntl(new_socket, F_GETFL, 0);
                    fcntl(new_socket, F_SETFL, flags | O_NONBLOCK);
                    pollfd new_fd;
                    new_fd.fd = new_socket;
                    new_fd.events = POLLIN;
                    poll_fds.push_back(new_fd);
                    client[new_fd.fd] = Client(); //create a new object of client and add it to the map by its fd as a key
                }
                else{
                    char buffer[1048];
                    memset(buffer, 0, sizeof(buffer));
                    int bytes = recv(poll_fds[i].fd, buffer, sizeof(buffer), 0);
                    if (bytes <= 0){
                        close(poll_fds[i].fd); //client deconnecte
                        std::cout<<"client : "<<poll_fds[i].fd<<" deconnecte"<<std::endl;
                        poll_fds.erase(poll_fds.begin() + i);
                    }
                    else{
                        buffer[bytes] = '\0';
                        client[poll_fds[i].fd].Buffer += buffer;
                        std::string cmds = client[poll_fds[i].fd].Buffer;
                        extract_cmds(cmds);
                        // and then try to extract all complete commands and store them in messages
                        //handle_client_data(vector<std::string>);
                        std::cout<< "Received : "<<buffer<< " from :" <<poll_fds[i].fd<<std::endl;
                        // client[poll_fds[i].fd].Buffer = buffer; //later i will add a function for it
                    }
                }
            }
        }
    }
}

void Server::extract_cmds(std::string cmds){
    for(int i =0; i<cmds.length(); i++){
        size_t pos = cmds.find("\r\n");
        if (pos != std::string::pos){

        }
        else{
            
        }
    }
}
