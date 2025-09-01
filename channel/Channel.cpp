#include "Channel.hpp"

Channel::Channel():Name("default") , _capacityLimit(-1), _membersCount(0)
, _i(false), _t(false), _k(false), _l(false)
{
    // this->_members.clear();
    // this->_Ops.clear();
}

Channel::Channel( const std::string name ): Name(name), _capacityLimit(-1), _membersCount(0)
, _i(false), _t(false), _k(false), _l(false)
{
    // this->_members.clear();
    // this->_Ops.clear();
}

Channel::~Channel(){}

const std::map<std::string, Client >&
Channel::GetMembers(void)const {
return this->_members;
}

const std::map<std::string, Client >&
Channel::GetOps(void)const {
    return this->_Ops;
}

int
Channel::getCapacityLimit( void ) const 
{
    return this->_capacityLimit;
}

uint
Channel::getMembersCount( void ) const 
{
    return this->_membersCount;
}

std::string
Channel::getModes( void ) const 
{
    return this->_modes;
}

bool
Channel::is_Op( const std::string &name ) const
{
    std::map<std::string, Client>::const_iterator it = this->_Ops.find(name);

    return (it != this->_Ops.end()) ? true : false;
}

bool
Channel::is_restrectedTopic( void )const
{
    return this->_t;
}

bool
Channel::is_userLimited( void )const
{
    return this->_l;
}
bool
Channel::is_inviteOnly( void )const
{
    return this->_i;
}
bool
Channel::is_keyed( void )const
{
    return this->_k;
}

void
Channel::addModes( const std::string &mode )
{
    this->_modes += mode;
}

void Channel::rmMode(const std::string &mode)
{
    std::string::size_type pos = this->_modes.find(mode[0]);
    if (pos != std::string::npos) {
        this->_modes.erase(pos, 1); 
    }
}


void
Channel::addOps( Client &newOp )
{
    if (!is_Op(newOp.getnick()))
        this->_Ops[newOp.getnick()] = newOp;

}

void
Channel::setKey( const std::string &password )
{
    this->Password = password;
}

void
Channel::setCapacityLimit( const std::string &num )
{
    std::stringstream   extract(num);
    int                 i;

    if ((extract >> i) && extract.eof())
    {
        if (i >= 0 && i >= static_cast<int>(this->getMembersCount()))
        {
            this->_capacityLimit = i;
            this->triggerMode("+", "l", this->is_userLimited(), this->_l);
        }

    }
        
}


void
Channel::triggerMode( const std::string flag , const std::string mode, const bool isMode, bool &toTrigger )
{
    if (flag == "+" && !isMode)
    {
        this->addModes(mode);
        toTrigger = true;
    }
    else if (flag == "-" && isMode)
    {
        this->rmMode(mode);
        toTrigger = false;
    }

}

void
Channel::incrementCount( void )
{
    this->_membersCount++;
}

void
Channel::decrementCount( void )
{
    this->_membersCount--;
}

std::string& Channel::GetName(void){return Name;}

void Channel::SetName(std::string& name){Name=name;}

std::string& Channel::GetPassword(void){
    return Password;
}
