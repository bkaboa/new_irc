#include "../../include/server/server.hpp"
#include <utility>

using namespace irc;

void	Server::channelNew(Channel &newChannel)
{
	if (_ChannelMap.find())
	_ChannelMap.insert(std::make_pair(fd_t, newChannel));
}
