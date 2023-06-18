#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"
#include <unistd.h>

using namespace irc;

void	Server::clientNew(fd_t clientFd)
{
	if (_ClientMap.find(clientFd) != _ClientMap.end())
	{
		std::cout << RED << "Error : this file descriptor is already taken" << NC << '\n';
		_PollVector.pop_back();
	}
	else
	{
		std::cout << GREEN << "New client connection established from " << NC << '\n';
		_ClientMap.insert(std::make_pair(clientFd, new Client(clientFd)));
	}
}

void	Server::disconnectClient(pollvectorIter &it)
{
	mapClientIter mit = _ClientMap.find(it->fd);

	if (mit->second->getName().empty())
	{
		std::cout << BLUE << "Unknown client disconnected" << NC << std::endl;
		delete mit->second;
		_ClientMap.erase(mit);
	}
	else {
		std::cout << BLUE << "Client " << mit->second->getNick() << " disconnected" << NC << std::endl;
		delete mit->second;
		_ClientMap.erase(mit);
	}
	close(it->fd);
	_PollVector.erase(it);
}

void	Server::deleteAllClient()
{
	for (mapClient::iterator it = _ClientMap.begin(); it != _ClientMap.end(); it++)
	{

		std::cout << GREEN << "disconnect client " << it->second->getName() << NC << '\n';
		delete it->second;
		close(it->first);
	}
}
