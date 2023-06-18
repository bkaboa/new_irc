#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"
#include "../../include/channel/channel.hpp"

using namespace irc;

void Server::Invite(fd_t sender, const commandData_t &args)
{
	if (!_ClientMap[sender]->isRegistered())
	{
		sendStr(sender, ERR_NOTREGISTERED(_ClientMap[sender]->getNick()));
		return;
	}
	if (args.binParams == NONE || !(args.binParams & NICK) || !(args.binParams & TARG))
	{
		sendStr(sender, ERR_NEEDMOREPARAMS(_ClientMap[sender]->getNick(), "INVITE"));
		return;
	}
	std::string notif = "You've been invited to channel ";
	std::string targetNick = args.params[0];
	std::string targetChannel = args.params[1];
	fd_t		targetFd = getClientFd(targetNick);
	if (targetFd == -1)
		return;
	if ((targetChannel[0] == '#' || targetChannel[0] == '&') && _ChannelMap.find(targetChannel) != _ChannelMap.end())
	{
		Channel *channel = _ChannelMap.find(targetChannel)->second;
		notif += targetChannel + " by user " + _ClientMap[sender]->getNick() + "\r\n";
		if (!channel->isInChannel(sender))
		{
			sendStr(sender, ERR_NOTONCHANNEL(_ClientMap[sender]->getNick(), targetChannel));
			return;
		}
		else
		{
			//invite only for operators, add to list
			if (channel->getOptions() & i)
			{
				if (channel->isAdmin(sender))
				{
					sendStr(targetFd, notif);
					channel->addInvite(targetFd);
				}
				else
					sendStr(sender, ERR_CHANOPRIVSNEEDED(_ClientMap[sender]->getNick(), targetChannel));
				return;
			}
			//public invite
			else if (!(channel->getOptions() & i))
			{
				sendStr(targetFd, notif);
				sendStr(sender, RPL_INVITING(_ClientMap[sender]->getNick(), targetNick, targetChannel));
				return;
			}
		}
	}
	sendStr(sender, ERR_NOSUCHCHANNEL(_ClientMap[sender]->getNick(), targetChannel));
	return;
}