#include "Channel.hpp"

Channel::Channel():op(0),Name(""){

}

Channel::~Channel(){

}

Channel::Channel(std::string name):op(0),Name(name){

}

std::string& Channel::GetName(void){return Name;}