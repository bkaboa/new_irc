#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"
#include "../../include/channel/channel.hpp"

using namespace irc;

void Server::Part(fd_t sender, const commandData_t &args)
{
	if (!_ClientMap[sender]->isRegistered())
	{
		sendStr(sender, ERR_NOTREGISTERED(_ClientMap[sender]->getNick()));
		return;
	}
	if (args.binParams == NONE || !(args.binParams & CHAN))
	{
		sendStr(sender, ERR_NEEDMOREPARAMS(_ClientMap[sender]->getNick(), "PART"));
		return;
	}
	std::string reason;
	if (args.binParams & MESS)
		reason = args.params[1];
	else if (!(args.binParams & MESS))
		reason = ": No particular reason";
	std::vector<std::string> channelsToPart;
	channelsToPart = strSplit(args.params[0], ',');

	//TEST pour voir si les channels sont bien presents
	for (std::vector<std::string>::iterator itera = channelsToPart.begin(); itera != channelsToPart.end(); ++itera)
	{
		if (!((*itera)[0] == '#' || (*itera)[0] == '&'))
			sendStr(sender, ERR_NOSUCHCHANNEL(_ClientMap[sender]->getNick(), *itera));
		else if (_ChannelMap.find(*itera) == _ChannelMap.end())
		{
			sendStr(sender, ERR_NOSUCHCHANNEL(_ClientMap[sender]->getNick(), *itera));
		}
		else if (_ChannelMap.find(*itera) != _ChannelMap.end())
		{
			Channel *chan = _ChannelMap.find(*itera)->second;
			if (chan->isInChannel(sender))
			{
				chan->removeMember(sender);
				std::string reply = ":" + _ClientMap[sender]->getNick() + "!" + _ClientMap[sender]->getName() + " PART " + chan->getName() + "\r\n";
				chan->channelMsg(-1, reply);
				sendStr(sender, reply);
				if (chan->getNumClients() == 0)
					deleteChannel(chan->getName());
			}
			else if (!chan->isInChannel(sender))
				sendStr(sender, ERR_NOTONCHANNEL(_ClientMap[sender]->getNick(), chan->getName()));
		}
	}
}
