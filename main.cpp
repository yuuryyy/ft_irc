#include "server/Server.hpp"

int main(){
    Server test;
    Client tst;
    tst.AddBuffer("hajar\r\nfiqar\r\nlili");
    tst.extract_cmds();
    std::cout<<"rest : "<<tst.getBuffer()<<std::endl;
    std::vector<std::string>& cmd = tst.getCmds();
    for(size_t i =0; i < cmd.size(); i++){
        std::cout<<"cmd "<<i<<" : "<<cmd[i]<<std::endl;
    }
    test.server_socket();
}