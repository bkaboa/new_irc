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
			//channel does not exist
			if (_ChannelMap.find(*iter) == _ChannelMap.end())
			{
				std::string newChanName = *iter;
				if (newChanName[0] == '#' || newChanName[0] == '&')
				{
					if (args.binParams & PASS)
					{
						channelNew(_ClientMap[sender], newChanName, args.params[1]);
						std::string reply = ":" + _ClientMap[sender]->getNick() + "!" + _ClientMap[sender]->getName() + " JOIN " + newChanName + "\r\n";
						sendStr(sender, reply);
						if (!(_ChannelMap[newChanName]->getTopic().empty()))
							sendStr(sender, RPL_TOPIC(_ClientMap[sender]->getNick(), _ChannelMap[newChanName]->getName(), _ChannelMap[newChanName]->getTopic()));
						sendStr(sender, RPL_NAMREPLY(_ClientMap[sender]->getName(), "!", newChanName, "@", _ClientMap[sender]->getNick(), ""));
						sendStr(sender, RPL_ENDOFNAMES(_ClientMap[sender]->getName(), newChanName));
					}
					else
					{
						channelNew(_ClientMap[sender], newChanName, "");
						std::string reply = ":" + _ClientMap[sender]->getNick() + "!" + _ClientMap[sender]->getName() + " JOIN " + newChanName + "\r\n";
						sendStr(sender, reply);
						if (!(_ChannelMap[newChanName]->getTopic().empty()))
							sendStr(sender, RPL_TOPIC(_ClientMap[sender]->getNick(), _ChannelMap[newChanName]->getName(), _ChannelMap[newChanName]->getTopic()));
						sendStr(sender, RPL_NAMREPLY(_ClientMap[sender]->getName(), "!", newChanName, "@", _ClientMap[sender]->getNick(), ""));
						sendStr(sender, RPL_ENDOFNAMES(_ClientMap[sender]->getName(), newChanName));
					}
				}
				else 
					sendStr(sender, "To create a Channel, you need to add the prefix # or &\r\n");
			}
			//channel does exist
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
							{
								chan->addMember(_ClientMap[sender], 0);
								std::string reply = ":" + _ClientMap[sender]->getNick() + "!" + _ClientMap[sender]->getName() + " JOIN " + chan->getName() + "\r\n";
								sendStr(sender, reply);
								if (!(chan->getTopic().empty()))
									sendStr(sender, RPL_TOPIC(_ClientMap[sender]->getNick(), chan->getName(), chan->getTopic()));
								sendStr(sender, RPL_NAMREPLY(_ClientMap[sender]->getName(), "!", chan->getName(), "@", _ClientMap[sender]->getNick(), ""));
								sendStr(sender, RPL_ENDOFNAMES(_ClientMap[sender]->getName(), chan->getName()));
							}
						}
						else
						{
							sendStr(sender, ERR_BADCHANNELKEY(_ClientMap[sender]->getName(), chan->getName()));
						}
					}
					else
					{
						chan->addMember(_ClientMap[sender], 0);
						std::string reply = ":" + _ClientMap[sender]->getNick() + "!" + _ClientMap[sender]->getName() + " JOIN " + chan->getName() + "\r\n";
						sendStr(sender, reply);
						if (!(chan->getTopic().empty()))
							sendStr(sender, RPL_TOPIC(_ClientMap[sender]->getNick(), chan->getName(), chan->getTopic()));
						sendStr(sender, RPL_NAMREPLY(_ClientMap[sender]->getName(), "!", chan->getName(), "@", _ClientMap[sender]->getNick(), ""));
						sendStr(sender, RPL_ENDOFNAMES(_ClientMap[sender]->getName(), chan->getName()));
					}
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