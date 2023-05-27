#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

void Server::Pass(fd_t sender, std::vector<std::string> args)
{
	std::string pass = args[0];
	if (_ClientMap[sender]->isRegistered())
	{
		//ERR_ALREADYREGISTERED
		return;
	}
	if (pass.compare(_Password) == 0)
	{
		_ClientMap[sender]->setPassOk(true);
		return;
	}
	else if (pass.compare(_Password) != 0)
	{
		_ClientMap[sender]->setPassOk(false);
		//ERR_PASSWDMISMATCH
		return;
	}
}