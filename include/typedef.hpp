#pragma once

#include "include.hpp"

namespace irc
{
	class Client;
	struct Member;
}
//base typedef
typedef	u_int32_t		fd_t;
typedef u_int16_t		socket_t;

//typdef on pollfd vector and pollfd iterator
typedef std::vector<struct pollfd>					pollvector;
typedef std::vector<struct pollfd>::iterator		pollvectorIter;

//client stockage in map with a typdef on iterator
typedef std::map<fd_t, irc::Client*>				mapClient;
typedef std::map<fd_t, irc::Client*>::iterator	mapClientIter;

//typedef for channel Client list
typedef std::vector<irc::Member> channelMembers;
