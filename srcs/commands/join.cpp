#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"
#include "../../include/channel/channel.hpp"

using namespace irc;

void Server::Join(fd_t sender, const commandData_t &args)
{
	std::cout << NC << "Client with fd " << sender << " requested a Join command" << std::endl;
	if (args.binParams == NONE)
		sendStr(sender, ERR_NEEDMOREPARAMS(_ClientMap[sender]->getNick(), "JOIN"));
	else if (_ChannelMap.size() < MAX_CHANNELS)
	{
		std::vector<std::string> channelsToJoin = strSplit(args.params[0], ',');
		std::vector<std::string>::iterator iter = channelsToJoin.begin();

		for (; iter != channelsToJoin.end(); ++iter)
		{
			if (_ChannelMap.find(*iter) == _ChannelMap.end())
			{
				std::string newChanName = *iter;
				if (newChanName[0] == '#' || newChanName[0] == '&')
				{
					if (args.binParams & PASS)
						channelNew(_ClientMap[sender], newChanName, args.params[1]);
					else
					{
						std::string j = "JOIN " + newChanName + "\r\n";
						channelNew(_ClientMap[sender], newChanName, "");
						send(sender, j.c_str(), j.size(), 0);
					}
				}
				else 
					sendStr(sender, "To create a Channel, you need to add the prefix # or &\r\n");
			}
			else
			{
				Channel *chan = _ChannelMap[*iter];
				if (!(chan->isInChannel(sender)))
				{
					if (!(chan->getPass().empty()))
					{
						if (args.binParams & PASS)
						{
							if (chan->checkPass(args.params[1]))
								chan->addMember(_ClientMap[sender], 0);
						}
						else
						{
							sendStr(sender, ERR_BADCHANNELKEY(_ClientMap[sender]->getName(), chan->getName()));
						}
					}
					else
						chan->addMember(_ClientMap[sender], 0);
				}
				else if (chan->isInChannel(sender))
				{
					sendStr(sender, ERR_USERONCHANNEL(_ClientMap[sender]->getName(), _ClientMap[sender]->getNick(), chan->getName()));
					return;
				}
			}
		}
	}
}