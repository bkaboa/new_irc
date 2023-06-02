#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

static bool	nameExist(std::string name, mapClient &map)
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
	std::cout << NC << "Client with fd " << sender << " requested a Nick command" << std::endl;
	if (!(cmd.binParams & PASS))
	{
		sendStr(sender, ERR_NEEDMOREPARAMS(_ClientMap[sender]->getNick(), cmd.originalCommand));
		return;
	}
	std::string name = cmd.params[0];
	if (this->_ClientMap[sender]->isConnect())
	{
		if (!nameExist(name, this->_ClientMap))
		{
			this->_ClientMap[sender]->changeNick(name);
			return;
		}
		else if (nameExist(name, this->_ClientMap))
		{
			//ERR_NICKNAMEINUSE
			return;
		}
	}
	//we are not registered and need to check if pass is ok and if nick is ok
	else if (!this->_ClientMap[sender]->isConnect())
	{
		if (!this->_ClientMap[sender]->getPassOk())
		{
			//bad
			return;
		}
		if (this->_ClientMap[sender]->getPassOk())
		{
			if (nameExist(name, this->_ClientMap))
			{
				this->_ClientMap[sender]->setPassOk(false);
				return;
			}
			else if (!nameExist(name, this->_ClientMap))
			{
				this->_ClientMap[sender]->changeNick(name);
				this->_ClientMap[sender]->setNickOk(true);
			}
			return;
		}
	}
}
