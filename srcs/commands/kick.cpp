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
		std::string reason = " :no particuliar reason";
		if (args.binParams & MESS)
			reason = " " + args.params[2];
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
						std::string reply = ":" + _ClientMap[sender]->getNick() + "!" + _ClientMap[sender]->getName() + " KICK " + chantarget + " " + target + reason + "\r\n";
						chan->channelMsg(-1, reply);
						chan->kickMember(targetFd);
					}
					else
						sendStr(sender, ERR_USERNOTINCHANNEL(_ClientMap[sender]->getNick(), target, chantarget));
				}
				else
					sendStr(sender, ERR_CHANOPRIVSNEEDED(_ClientMap[sender]->getNick(), chantarget));
			}
			else
				sendStr(sender, ERR_NOTONCHANNEL(_ClientMap[sender]->getNick(), chantarget));
		}
		else
			sendStr(sender, ERR_NOSUCHCHANNEL(_ClientMap[sender]->getNick(), chantarget));
	}
}