#include "../../include/include.hpp"
#include "../../include/IrcMessage/IrcMessage.hpp"
#include "../../include/server/server.hpp"
#include "../../include/channel/channel.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

void Server::Privmsg(fd_t sender, const commandData_t &args)
{
	if (!(args.binParams & MESS))
		;//ERR_NOTEXTTOSEND
	
}
