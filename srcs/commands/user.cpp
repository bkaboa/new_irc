#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

void Server::User(fd_t sender, std::vector<std::string> args)
{
	if (_ClientMap[sender]->isConnect())
	{
		std::string newname = args[0];
		_ClientMap[sender]->changeName(newname);
	}
	// else
	// 	sendStr("Cant change name");
}