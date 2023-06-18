#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

static bool	userExist(fd_t sender, std::string name, mapClient &map)
{
	mapClientIter iter;
	for(iter = map.begin(); iter != map.end(); ++iter)
	{
		if (sender != iter->first)
		{
			if (iter->second->getName().compare(name.c_str()) == 0)
				return (true);
		}
	}
	return (false);
}

void Server::User(fd_t sender, const commandData_t &cmd)
{
	if (cmd.binParams == NONE || !(cmd.binParams & USER))
	{
		sendStr(sender, ERR_NEEDMOREPARAMS(_ClientMap[sender]->getNick(), "USER"));
		return;
	}
	std::string newname = cmd.params[0];
	if (_ClientMap[sender]->isRegistered())
	{
		sendStr(sender, ERR_ALREADYREGISTERED(_ClientMap[sender]->getNick()));
		return;
	}
	else if (!_ClientMap[sender]->isRegistered())
	{
		_ClientMap[sender]->changeName(newname);
		_ClientMap[sender]->setUserOk(true);
		if (_ClientMap[sender]->getPassOk() && _ClientMap[sender]->getNickOk() && _ClientMap[sender]->getUserOk())
		{
			_ClientMap[sender]->setIsRegistered(true);
			sendStr(sender, "You successfuly registered !\r\n");
			sendStr(sender, RPL_WELCOME(_ClientMap[sender]->getNick(), SERVER_NAME, _ClientMap[sender]->getNick()));
		}
	}
}
