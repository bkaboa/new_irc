#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

static void nickMessage(fd_t sender, std::string previousNick, std::string newnick)
{
	if (previousNick.empty())
		previousNick = "new client";
	std::string mess = std::string(":") + previousNick + " NICK " + newnick + "\r\n";
	sendStr(sender, mess);
}

static bool	nickExist(fd_t sender, std::string name, mapClient &map)
{
	mapClientIter iter;
	for(iter = map.begin(); iter != map.end(); ++iter)
	{
		if (sender != iter->first)
		{
			if (iter->second->getNick().compare(name.c_str()) == 0)
				return (true);
		}
	}
	return (false);
}

void Server::Nick(fd_t sender, const commandData_t &cmd)
{
	if (!(cmd.binParams & NICK))
	{
		sendStr(sender, ERR_NONICKNAMEGIVEN(_ClientMap[sender]->getNick()));
		if(!_ClientMap[sender]->isRegistered())
			_ClientMap[sender]->setNickOk(false);
		return;
	}
	std::string newnick = cmd.params[0];
	if (_ClientMap[sender]->getNick().compare(newnick) == 0)
	{
		sendStr(sender, "Please enter a nickname different from your current one\r\n");
		return;
	}
	if (!nickExist(sender, newnick, _ClientMap))
	{
		std::string newNameReply = "New nick available, your nickname is now " + newnick + "\r\n";
		nickMessage(sender, _ClientMap[sender]->getNick(), newnick);
		this->_ClientMap[sender]->changeNick(newnick);
		if(!_ClientMap[sender]->isRegistered())
			_ClientMap[sender]->setNickOk(true);
		sendStr(sender, newNameReply);
		return;
	}
	else if (nickExist(sender, newnick, _ClientMap))
	{
		if(!_ClientMap[sender]->isRegistered())
			_ClientMap[sender]->setNickOk(false);
		sendStr(sender, ERR_NICKNAMEINUSE(_ClientMap[sender]->getNick(), newnick));
		return;
	}
}
