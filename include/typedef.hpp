#pragma once

#include "include.hpp"
#include <list>
#include <vector>

namespace irc
{
	class Client;
	class Channel;
}
//base typedef
typedef	int32_t			fd_t;
typedef int32_t			socket_t;

//typdef on pollfd vector and pollfd iterator
typedef std::vector<struct pollfd>				pollvector;
typedef std::vector<struct pollfd>::iterator	pollvectorIter;

//client stockage in map with a typdef on iterator
typedef std::map<fd_t, irc::Client*>			mapClient;
typedef std::map<fd_t, irc::Client*>::iterator	mapClientIter;

//typedef for channel list
typedef std::map<std::string, irc::Channel*>				mapChannel;
typedef std::map<std::string, irc::Channel&>::iterator	mapChannelIter;

//typedef for Client list in Channel
typedef std::map<fd_t, irc::Client&>	mapChannelClient;
typedef mapChannelClient::iterator		mapChannelClientIter;

//typedef for client option in channel
typedef std::map<fd_t, int>				optionClientInChannel;
typedef optionClientInChannel::iterator optionClientInChannelIter;

//typdef for store the client fd
typedef std::vector<fd_t>			vectorFdClient;
typedef std::vector<fd_t>::iterator	vectorFdClientIter;

//Command list
typedef std::list<struct commandData_t>	commandList;



//IrcMessage Data
struct commandData_t{
	fd_t							clientRequest;
	int								command;
	std::string						originalCommand;
	int								binParams;
	std::vector<std::string>		params;
};
