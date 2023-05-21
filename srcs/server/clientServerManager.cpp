#include "../../include/server/server.hpp"

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
		std::cout << GREEN << "new client connection established from " << NC << '\n';
		_ClientMap.insert(std::make_pair(clientFd, new Client(clientFd)));
	}
}

void	Server::disconnectClient(pollvectorIter &it)
{
	mapClientIter mit = _ClientMap.find(it->fd);

	if (mit->second->getName().empty())
	{
		std::cout << BLUE << "Unknown client disconnected" << NC << std::endl;
		_ClientMap.erase(mit);
	}
	else {
		std::cout << BLUE << "client " << mit->second->getNick() << " disconnected" << NC << std::endl;
		_ClientMap.erase(mit);
	}
	_PollVector.erase(it);
}
