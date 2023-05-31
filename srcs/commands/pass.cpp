#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

void Server::Pass(fd_t sender, const commandData_t &cmd)
{
	std::string pass = "lol";
	if (_ClientMap[sender]->isConnect())
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
