#include "server/Server.hpp"

int main(){
    Server test(6667, "hajar");
    test.parse_cmd(":nick!user@host JOIN #channel :Hello everyone!");
    test.server_socket();
}