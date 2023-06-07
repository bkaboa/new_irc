#include "../../include/include.hpp"
#include "../../include/IrcMessage/IrcMessage.hpp"
#include "../../include/server/server.hpp"
#include "../../include/channel/channel.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

void Server::Privmsg(fd_t sender, const commandData_t &args)
{
	std::cout << NC << "Client with fd " << sender << " requested a Privmsg command" << std::endl;
	if (!(args.binParams & MESS))
		sendStr(sender, ERR_NOTEXTTOSEND(_ClientMap[sender]->getName()));
	else if (args.binParams & MESS)
	{
		std::string message = args.params[1];
		//multiple targets
		if (args.params[0].find(',') != npos)
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
						_ChannelMap[target]->channelMsg(message);
					}
					else
						sendStr(sender, ERR_NOSUCHCHANNEL(_ClientMap[sender]->getName(), target));
				}
				//target is a user
				else
				{
					mapClientIter clientiter = _ClientMap.begin();
					for (; clientiter != _ClientMap.end(); ++clientiter)
					{
						if (clientiter->second->getNick().compare(target.c_str()) == 0)
						{

							sendStr(clientiter->first, message);
						}
					}
				}
			}
		}
		//single target
		else
		{
			std::cout << YELLOW << "PRIVMSG SINGLE TARGET" << std::endl;
			std::string target = args.params[0];
			//target is a channel
			if (target[0] == '#' || target[0] == '&')
			{
				if (_ChannelMap.find(target) != _ChannelMap.end())
					_ChannelMap[target]->channelMsg(message);
				else
					sendStr(sender, ERR_NOSUCHCHANNEL(_ClientMap[sender]->getName(), target));
			}
			//target is a user
			else
			{
				if (_ClientMap)
			}
		}
		std::cout << GREEN << "PRIVMSG MSG " << args.params[1] << std::endl;
	}
}
