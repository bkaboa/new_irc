#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

void Server::Pass(fd_t sender, const commandData_t &cmd)
{
	if (!(cmd.binParams & PASS))
	{
		sendStr(sender, ERR_NEEDMOREPARAMS(_ClientMap[sender]->getNick(), cmd.originalCommand));
		return;
	}
	std::string pass = cmd.params[0];
	if (_ClientMap[sender]->isConnect())
	{
		sendStr(sender, ERR_ALREADYREGISTERED(_ClientMap[sender]->getNick()));
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
		sendStr(sender, ERR_PASSWDMISMATCH(_ClientMap[sender]->getNick()));
		return;
	}
}
