// #include "../../include/server/server.hpp"
// #include "../../include/client/client.hpp"

// using namespace irc;

// static bool nameExist(std::string name, mapClient &map)
// {
// 	mapClientIter iter;
// 	for (iter = map.begin(); iter != map.end(); ++iter)
// 	{
// 		Client *client = iter->second;
// 		if (client->getName().compare(name.c_str()) == 0)
// 			return (true);
// 	}
// 	return (false);
// }

// void Server::User(fd_t sender, std::vector<std::string> args)
// {
// 	std::string newname = args[0];
// 	//if already registered
// 	if (_ClientMap[sender]->isConnect() && newname.compare(_ClientMap[sender]->getName()) != 0)
// 	{
// 		if (nameExist(newname, _ClientMap))
// 			_ClientMap[sender]->changeName(_ClientMap[sender]->getNick());
// 		else if (!nameExist(newname, _ClientMap))
// 			_ClientMap[sender]->changeName(newname);
// 		_ClientMap[sender]->changeName(newname);
// 		return;
// 	}
// 	//if not registered
// 	else if (!_ClientMap[sender]->isConnect())
// 	{
// 		if (!_ClientMap[sender]->getPassOk() || !_ClientMap[sender]->getNickOk())
// 		{
// 			//authent error pass or nick not ok
// 			_ClientMap[sender]->setPassOk(false);
// 			_ClientMap[sender]->setNickOk(false);
// 			return;
// 		}
// 		else if (_ClientMap[sender]->getPassOk() && _ClientMap[sender]->getNickOk())
// 		{
// 			//if username exist we use the nickname, else we change the username and registration is done
// 			if (nameExist(newname, _ClientMap))
// 				_ClientMap[sender]->changeName(_ClientMap[sender]->getNick());
// 			else if (!nameExist(newname, _ClientMap))
// 				_ClientMap[sender]->changeName(newname);
// 			_ClientMap[sender]->setIsRegistered(true);
// 			return;
// 		}
// 	}
// }
