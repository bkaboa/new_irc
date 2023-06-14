#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

static bool	nickExist(std::string name, mapClient &map)
{
	mapClientIter iter;
	for(iter = map.begin(); iter != map.end(); ++iter)
	{
		Client *client = iter->second;
		if (client->getNick().compare(name.c_str()) == 0)
			return (true);
	}
	return (false);
}

void Server::Nick(fd_t sender, const commandData_t &cmd)
{
	if (!(cmd.binParams & NICK))
	{
		sendStr(sender, ERR_NEEDMOREPARAMS(_ClientMap[sender]->getNick(), cmd.originalCommand));
		return;
	}
	std::string name = cmd.params[0];
	if (this->_ClientMap[sender]->isRegistered())
	{
		if (!nickExist(name, this->_ClientMap))
		{
			this->_ClientMap[sender]->changeNick(name);
			return;
		}
		else if (nickExist(name, this->_ClientMap))
		{
			sendStr(sender, ERR_NICKNAMEINUSE(_ClientMap[sender]->getNick(), name));
			return;
		}
	}
	//we are not registered and need to check if pass is ok and if nick is ok
	else if (!this->_ClientMap[sender]->isRegistered())
	{
		if (!this->_ClientMap[sender]->getPassOk())
		{
			sendStr(sender, ERR_PASSWDMISMATCH(_ClientMap[sender]->getName()));
			_ClientMap[sender]->setPassOk(false);
			_ClientMap[sender]->setNickOk(false);
			_ClientMap[sender]->setUserOk(false);
			return;
		}
		if (this->_ClientMap[sender]->getPassOk())
		{
			if (nickExist(name, this->_ClientMap))
			{
				_ClientMap[sender]->setPassOk(false);
				_ClientMap[sender]->setNickOk(false);
				_ClientMap[sender]->setUserOk(false);
				sendStr(sender, ERR_NICKNAMEINUSE("new client", name));
				return;
			}
			else if (!nickExist(name, this->_ClientMap))
			{
				this->_ClientMap[sender]->changeNick(name);
				this->_ClientMap[sender]->setNickOk(true);
				if (_ClientMap[sender]->getPassOk() && _ClientMap[sender]->getNickOk() && _ClientMap[sender]->getUserOk())
				{
					_ClientMap[sender]->setIsRegistered(true);
					sendStr(sender, "You successfuly registered !\r\n");
				}
			}
			return;
		}
	}
}
