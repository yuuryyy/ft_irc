#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#pragma once
#include <string>
#include "Client.hpp"
#include "Server.hpp"


class Channel {
    private:
        std::string Name;
        std::string Password;

        uint                                    _creationTime;
        int                                     _capacityLimit;
        uint                                    _membersCount;
        std::map<std::string, Client>           _members;
        std::string                             _modes;
        std::map<std::string, Client>           _Ops;

        bool                                    _i;
        bool                                    _t;
        bool                                    _k;
        bool                                    _l;
        
        const std::map<std::string, Client >&    GetMembers(void) const;
        const std::map<std::string, Client >&    GetOps(void) const;

        
        int                                     getCapacityLimit( void ) const;
        uint                                    getMembersCount( void ) const;
        
        bool                                    is_Op( const std::string &name ) const;
        bool                                    is_restrectedTopic( void ) const;
        bool                                    is_userLimited( void ) const;
        bool                                    is_inviteOnly( void ) const;
        bool                                    is_keyed( void ) const;
        
        
        void                                    addModes( const std::string &mode );
        void                                    rmMode(const std::string &mode );
        void                                    addOps( Client &newOp );
        
        void                                    setKey( const std::string &password ) ;
        void                                    setCapacityLimit( const std::string  &num );
        
        void                                    triggerMode( const std::string flag , const std::string mode, const bool isMode, bool &toTrigger ) ;
        
        void                                    incrementCount( void );
        void                                    decrementCount( void );
        
        public:
        
        Channel();
        Channel( const std::string name );
        ~Channel();
        
        std::string                              getModes( void ) const;
        const   uint                             getTime( void )const;

        std::string& GetName(void);
        void SetName(std::string& name);
        std::string& GetPassword(void);
        
        // const bool getModes( void ) const;
        // const bool getModes( void ) const;
        //get username of ops
};

#endif