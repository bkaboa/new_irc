#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

static bool nameExist(std::string name, mapClient &map)
{
	mapClientIter iter;
	for (iter = map.begin(); iter != map.end(); ++iter)
	{
		Client *client = iter->second;
		if (client->getName().compare(name) == 0)
			return (true);
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
	//if already registered
	if (_ClientMap[sender]->isRegistered() && newname.compare(_ClientMap[sender]->getName()) != 0)
	{
		_ClientMap[sender]->changeName(newname);
		return;
	}
	//if not registered
	else if (!_ClientMap[sender]->isRegistered())
	{
		if (!(_ClientMap[sender]->getPassOk()))
		{
			//authent error pass or nick not ok
			_ClientMap[sender]->setPassOk(false);
			_ClientMap[sender]->setNickOk(false);
			_ClientMap[sender]->setUserOk(false);
			return;
		}
		else if (_ClientMap[sender]->getPassOk())
		{

			_ClientMap[sender]->changeName(newname);
			_ClientMap[sender]->setUserOk(true);
			if (_ClientMap[sender]->getPassOk() && _ClientMap[sender]->getNickOk() && _ClientMap[sender]->getUserOk())
			{
				_ClientMap[sender]->setIsRegistered(true);
				sendStr(sender, "You successfuly registered !\r\n");
			}
			return;
		}
	}
}
