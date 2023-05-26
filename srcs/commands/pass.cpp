#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

void Server::Pass(fd_t sender, std::vector<std::string> args)
{
	if (!args[0].compare(_Password))
	{
		return;
	}
	else if (args[0].compare(_Password))
	{
		if ()
		_ClientMap[sender]->setIsConnect(true);
	}
}