#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"
#include "../../include/channel/channel.hpp"

using namespace irc;

void Server::List(fd_t sender, const commandData_t &args)
{
	if (!(_ClientMap[sender]->getIsRegistered()))
		return;
	if (args.binParams == NONE)
	{
		std::map<std::string, Channel*>::iterator iter = _ChannelMap.begin();
		sendStr(sender, RPL_LISTSTART(_ClientMap[sender]->getName()));
		for (; iter != _ChannelMap.end(); ++iter)
		{
			Channel *chan = iter->second;
			sendStr(sender, RPL_LIST(_ClientMap[sender]->getName(), iter->first, std::to_string(chan->getNumClients()), chan->getTopic()));
		}
		sendStr(sender, RPL_LISTEND(_ClientMap[sender]->getName()));
	}
}