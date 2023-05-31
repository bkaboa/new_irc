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

void Server::Nick(fd_t sender, std::vector<std::string> args)
{
	std::string name = args[0];
	//we are already registered and just want to change the nickname
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
