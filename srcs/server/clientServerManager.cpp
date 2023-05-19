#include "../../include/server/server.hpp"

using namespace irc;

void	Server::clientNew(fd_t clientFd)
{
	if (_ClientMap.find(clientFd) != _ClientMap.end())
	{
		std::cout << RED << "Error : this file descriptor is already taken" << NC << '\n';
	}
	else
	{
		std::cout << GREEN << "new client connection established" << NC << '\n';
		_ClientMap.insert(std::make_pair(clientFd, new Client(clientFd)));
	}
}

void	Server::disconnectClient(fd_t clientFd)
{
	mapClientIter	mIt;
	pollvectorIter	vIt;
	Client			clientTmp(clientFd);

	if ((mIt = _ClientMap.find(clientFd)) == _ClientMap.end())
	{
		std::cout << RED << "client in map doesn't exist" << NC << '\n';
	}
	else
	{
		clientTmp = *mIt->second;
		delete mIt->second;
		_ClientMap.erase(mIt);
		// std::cout << BLUE << "the client " << clientTmp.getNick() << " have been disconnected" << NC << '\n';
	}
	for (pollvectorIter vIt = _PollVector.begin(); vIt->fd != clientFd; vIt++);
	_PollVector.erase(vIt);
}
