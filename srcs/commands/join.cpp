#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"
#include "../../include/channel/channel.hpp"

using namespace irc;

void Server::Join(fd_t sender, const commandData_t &args)
{
	std::cout << NC << "Client with fd " << sender << " requested a Join command" << std::endl;
	if (args.binParams == NONE || !(args.binParams & CHAN))
		sendStr(sender, ERR_NEEDMOREPARAMS(_ClientMap[sender]->getNick(), "JOIN"));
	// else if (_ChannelMap.size() < _maxChannels)
	// {
	// 	std::vector<std::string> channelsToJoin = strSplit(args.params[0], ',');
	// 	std::vector<std::string>::iterator iter = channelsToJoin.begin();
	// 	for (; iter != channelsToJoin.end(); ++iter)
	// 	{
	// 		//channel does not exist
	// 		if (_ChannelMap.find(*iter) == _ChannelMap.end())
	// 		{

	// 		}
	// 		//channel does exist
	// 		else
	// 		{
	// 			Channel chan = _ChannelMap[*iter];
	// 			if (!(chan.isInChannel(sender)))
				
	// 		}
	// 	}
	// }
}