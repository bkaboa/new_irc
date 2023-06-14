#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"
#include "../../include/channel/channel.hpp"

using namespace irc;

void Server::Kick(fd_t sender, const commandData_t &args)
{
	if (!(args.binParams & NICK) || !(args.binParams & CHAN))
		sendStr(sender, ERR_NEEDMOREPARAMS(_ClientMap[sender]->getName(), "KICK"));
	else
	{
		std::string chantarget = args.params[0];
		std::string target = args.params[1];
		if (_ChannelMap.find(chantarget) != _ChannelMap.end())
		{
			Channel *chan = _ChannelMap.find(chantarget)->second;
			if (chan->isInChannel(sender))
			{
				if (chan->isAdmin(sender))
				{
					fd_t targetFd = getClientFd(target);
					if (targetFd != -1 && chan->isInChannel(targetFd) && sender != targetFd)
					{
						chan->kickMember(targetFd);
						std::string reply = ":" + _ClientMap[sender]->getNick() + "!" + _ClientMap[sender]->getName() + " KICK " + chantarget + " " + target + "\r\n";
						chan->channelMsg(-1, reply);
					}
				}
			}
			else
				sendStr(sender, ERR_NOTONCHANNEL(_ClientMap[sender]->getName(), chantarget));
		}
		else
		{
			sendStr(sender, ERR_NOSUCHCHANNEL(_ClientMap[sender]->getName(), chantarget));
		}
	}
}