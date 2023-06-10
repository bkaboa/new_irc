#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"
#include "../../include/channel/channel.hpp"

using namespace irc;

void Server::Join(fd_t sender, const commandData_t &args)
{
	if (!(_ClientMap[sender]->isRegistered()))
	{
		sendStr(sender, "You are not registered on this server...\r\n");
		return;
	}
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
					std::string reply = ":" + _ClientMap[sender]->getNick() + "!" + _ClientMap[sender]->getName() + " JOIN " + newChanName + "\r\n";
					//creating channel with password
					if (args.binParams & PASS && _ChannelMap.size() < MAX_CHANNELS)
					{
						channelNew(_ClientMap[sender], newChanName, args.params[1]);
						_ChannelMap[newChanName]->channelMsg(-1, reply);
						_ChannelMap[newChanName]->joinNameReply(sender, _ClientMap[sender]->getName());
					}
					//creating channel without pass
					else if (_ChannelMap.size() < MAX_CHANNELS)
					{
						channelNew(_ClientMap[sender], newChanName, "");
						_ChannelMap[newChanName]->channelMsg(-1, reply);
						_ChannelMap[newChanName]->joinNameReply(sender, _ClientMap[sender]->getName());
					}
					else
						sendStr(sender, ERR_TOOMANYCHANNELS(_ClientMap[sender]->getName(), newChanName));
				}
				else 
					sendStr(sender, "To create a Channel, you need to add the prefix # or &\r\n");
			}
			//channel does exist
			else
			{
				Channel *chan = _ChannelMap[*iter];
				//if user is not in channel
				if (!(chan->isInChannel(sender)))
				{
					//channel has password
					if (!(chan->getPass().empty()))
					{
						if (args.binParams & PASS)
						{
							if (chan->checkPass(args.params[1]))
							{
								chan->addMember(_ClientMap[sender], 0);
								std::string reply = ":" + _ClientMap[sender]->getNick() + "!" + _ClientMap[sender]->getName() + " JOIN " + chan->getName() + "\r\n";
								chan->channelMsg(-1, reply);
								chan->joinNameReply(sender, _ClientMap[sender]->getName());
							}
						}
						else
						{
							sendStr(sender, ERR_BADCHANNELKEY(_ClientMap[sender]->getName(), chan->getName()));
						}
					}
					//channel does not need password to be joined
					else
					{
						chan->addMember(_ClientMap[sender], 0);
						std::string reply = ":" + _ClientMap[sender]->getNick() + "!" + _ClientMap[sender]->getName() + " JOIN " + chan->getName() + "\r\n";
						chan->channelMsg(-1, reply);
						chan->joinNameReply(sender, _ClientMap[sender]->getName());
					}
				}
				else if (chan->isInChannel(sender))
					sendStr(sender, ERR_USERONCHANNEL(_ClientMap[sender]->getName(), _ClientMap[sender]->getNick(), chan->getName()));
			}
		}
	}
}