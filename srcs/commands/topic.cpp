#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"
#include "../../include/channel/channel.hpp"

using namespace irc;

void Server::Topic(fd_t sender, const commandData_t &args)
{
	//command need at least a channel
	if (args.binParams == NONE || !(args.binParams & CHAN))
	{
		sendStr(sender, ERR_NEEDMOREPARAMS(_ClientMap[sender]->getNick(), args.originalCommand));
		return;
	}
	else
	{
		std::string targetChan = args.params[0];
		//no channel
		if (_ChannelMap.find(targetChan) == _ChannelMap.end())
		{
			sendStr(sender, ERR_NOSUCHCHANNEL(_ClientMap[sender]->getNick(), targetChan));
			return;
		}
		//user not on channel
		if (!(_ChannelMap.find(targetChan)->second->isInChannel(sender)))
			sendStr(sender, ERR_NOTONCHANNEL(_ClientMap[sender]->getNick(), targetChan));
		//no message
		if (!(args.binParams & MESS))
		{
			if (_ChannelMap.find(targetChan)->second->getOptions() & t)
				sendStr(sender, RPL_TOPIC(_ClientMap[sender]->getNick(), targetChan, _ChannelMap.find(targetChan)->second->getTopic()));
			else
				sendStr(sender, RPL_NOTOPIC(_ClientMap[sender]->getNick(), targetChan));
			return;
		}
		//there is a message, we want to change or clear the topic
		if (args.binParams & MESS)
		{	
			if (!(_ChannelMap.find(targetChan)->second->isAdmin(sender)))
			{
				sendStr(sender, ERR_CHANOPRIVSNEEDED(_ClientMap[sender]->getNick(), targetChan));
				return;
			}
			if (!(_ChannelMap.find(targetChan)->second->getOptions() & t))
			{
				sendStr(sender, "Channel mode for topic is not set !\r\n");
				return;
			}
			std::string mess = args.params[1];
			if (mess[1] == ':')
				mess.erase(0,1);
			if (!mess[1])
			{
				_ChannelMap.find(targetChan)->second->setTopic("");
				return;
			}
			else
			{
				if (mess[0] == ':')
					mess.erase(0, 1);
				_ChannelMap.find(targetChan)->second->setTopic(mess);
				return;
			}
		}
	}
}