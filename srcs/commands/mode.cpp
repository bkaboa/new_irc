#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

void Server::Mode(fd_t sender, const commandData_t &args)
{
	// mode for channel only :
	//  i: Set/remove Invite-only channel
	//  t: Set/remove the restrictions of the TOPIC command to channel operators
	//  k: Set/remove the channel key (password)
	//  o: Give/take channel operator privilege
	//  l: Set/remove the user limit to channel
	if (!(_ClientMap[sender]->isRegistered()))
	{
		sendStr(sender, ERR_NOTREGISTERED(_ClientMap[sender]->getName()));
		return;
	}
	if (!(args.binParams & CHAN))
	{
		//err no chan in params
		return;
	}

}