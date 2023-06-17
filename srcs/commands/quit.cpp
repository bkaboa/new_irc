#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"
#include "../../include/channel/channel.hpp"

using namespace irc;

void Server::Quit(fd_t sender, const commandData_t &args)
{
	std::string reason = "Quit: Leaving\r\n";
	if (args.binParams & MESS)
		reason = "Quit " + args.params[0] + "\r\n";
	std::string reply = ":" + _ClientMap[sender]->getNick() + " QUIT " + reason;
	for (std::map<std::string, Channel *>::iterator iter = _ChannelMap.begin(); iter != _ChannelMap.end(); ++iter)
	{
		if (iter->second->isInChannel(sender))
		{
			iter->second->channelMsg(sender, reply);
			iter->second->removeMember(sender);
			if (iter->second->getNumClients() == 0)
				deleteChannel(iter->first);
		}
	}
	_ClientMap[sender]->setMustDeco();
}