#include "../../include/server/server.hpp"
#include "../../include/channel/channel.hpp"
#include <utility>

using namespace irc;

void	Server::channelNew(Client *creator, std::string name, std::string pass)
{
	_ChannelMap.insert(std::make_pair(name, new Channel(creator, name, pass)));
}

void Server::deleteChannel(std::string channame)
{
	for (mapChannel::iterator it = _ChannelMap.begin(); it != _ChannelMap.end(); it++)
	{
		if (it->first == channame)
		{
			delete it->second;
			_ChannelMap.erase(it);
		}
	}
	return;
}

void Server::deleteAllChannel()
{
	for (mapChannel::iterator it = _ChannelMap.begin(); it != _ChannelMap.end(); it++)
	{
		delete it->second;
	}
}
