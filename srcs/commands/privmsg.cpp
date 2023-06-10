#include "../../include/include.hpp"
#include "../../include/IrcMessage/IrcMessage.hpp"
#include "../../include/server/server.hpp"
#include "../../include/channel/channel.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

void Server::Privmsg(fd_t sender, const commandData_t &args)
{
	if (!(args.binParams & MESS))
		sendStr(sender, ERR_NOTEXTTOSEND(_ClientMap[sender]->getName()));
	else if (args.binParams & MESS)
	{
		std::string message = args.params[1];
		message += "\r\n";
		//multiple targets
		if (args.params[0].find(',') != std::string::npos)
		{
			std::vector<std::string> targets = strSplit(args.params[0], ',');
			std::vector<std::string>::iterator iter = targets.begin();
			for (; iter != targets.end(); ++iter)
			{
				std::string target = *iter;
				//target is a channel
				if (target[0] == '#' || target[0] == '&')
				{
					//channel exist in server
					if (_ChannelMap.find(target) != _ChannelMap.end())
					{
						_ChannelMap[target]->channelMsg(sender, message);
					}
					else
						sendStr(sender, ERR_NOSUCHCHANNEL(_ClientMap[sender]->getName(), target));
				}
				//target is a user
				else
				{
					fd_t targetfd = getClientFd(target);
					if (targetfd != -1)
					{
						sendStr(targetfd, message);
					}
					else
						sendStr(sender, ERR_NOSUCHNICK(_ClientMap[sender]->getName(), target));
				}
			}
		}
		//single target
		else
		{
			std::string target = args.params[0];
			//target is a channel
			if (target[0] == '#' || target[0] == '&')
			{
				std::string finalmsg = ":" + _ClientMap[sender]->getNick() + "!" + _ClientMap[sender]->getName() + "@" + SERVER_NAME + " PRIVMSG " + target + " " + message;
				if (_ChannelMap.find(target) != _ChannelMap.end())
				{
					if (_ChannelMap.find(target)->second->isInChannel(sender))
					{
						_ChannelMap[target]->channelMsg(sender, finalmsg);
					}
				}
				else
					sendStr(sender, ERR_NOSUCHCHANNEL(_ClientMap[sender]->getName(), target));
			}
			//target is a user
			else
			{
				fd_t targetfd = getClientFd(target);
				if (targetfd != -1)
				{
					std::string finalmsg = ":" + _ClientMap[sender]->getNick() + "!" + _ClientMap[sender]->getName() + "@" + SERVER_NAME + " PRIVMSG " + target + " " + message;
					sendStr(targetfd, finalmsg);
				}
				else
					sendStr(sender, ERR_NOSUCHNICK(_ClientMap[sender]->getName(), target));
			}
		}
	}
}
