#include "../../include/include.hpp"
#include "../../include/IrcMessage/IrcMessage.hpp"
#include "../../include/server/server.hpp"
#include "../../include/channel/channel.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

void Server::Privmsg(fd_t sender, const commandData_t &args)
{
	if (args.binParams)
		return;
	std::list<struct paramsData_t>::const_iterator it;
	for (it = args.params.begin(); it != args.params.end(); ++it)
	{
		//if target is channel
		if (it->type == CHAN)
		{
			Channel chan = *(this->_ChannelMap.find("some channel"))->second;
			chan.
		}
	}
}
