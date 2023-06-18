#include "../../include/include.hpp"
#include "../../include/IrcMessage/IrcMessage.hpp"
#include "../../include/server/server.hpp"
#include "../../include/channel/channel.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

void Server::Notice(fd_t sender, const commandData_t &args)
{
	if (!_ClientMap[sender]->isRegistered())
		return;
	if (!(args.binParams & MESS))
		return;
	if (!(args.binParams & TARG))
		return;
	else if (args.binParams & MESS)
	{
		std::string message = args.params[1];
		message += "\r\n";
		// multiple targets
		if (args.params[0].find(',') != std::string::npos)
		{
			std::vector<std::string> targets = strSplit(args.params[0], ',');
			std::vector<std::string>::iterator iter = targets.begin();
			for (; iter != targets.end(); ++iter)
			{
				std::string target = *iter;
				// target is a channel
				if (target[0] == '#' || target[0] == '&')
				{
					if (target[0] == '#' || target[0] == '&')
					{
						std::string finalmsg = "***" + _ClientMap[sender]->getNick() + " NOTICE " + target + " " + message;
						if (_ChannelMap.find(target) != _ChannelMap.end())
						{
							if (_ChannelMap.find(target)->second->isInChannel(sender))
								_ChannelMap[target]->channelMsg(sender, finalmsg);
						}
					}
				}
				// target is a user
				else
				{
					fd_t targetfd = getClientFd(target);
					if (targetfd != -1)
						sendStr(targetfd, message);
				}
			}
		}
		// single target
		else
		{
			std::string target = args.params[0];
			// target is a channel
			if (target[0] == '#' || target[0] == '&')
			{
				std::string finalmsg = ":" + _ClientMap[sender]->getNick() + " PRIVMSG " + target + " " + message;
				if (_ChannelMap.find(target) != _ChannelMap.end())
				{
					if (_ChannelMap.find(target)->second->isInChannel(sender))
						_ChannelMap[target]->channelMsg(sender, finalmsg);
				}
			}
			// target is a user
			else
			{
				fd_t targetfd = getClientFd(target);
				if (targetfd != -1)
				{
					std::string finalmsg = ":" + _ClientMap[sender]->getNick() + " PRIVMSG " + target + " " + message;
					sendStr(targetfd, finalmsg);
				}
			}
		}
	}
}
