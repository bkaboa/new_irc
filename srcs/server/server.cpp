#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"
#include <vector>

using namespace irc;

Server::Server(std::string portStr, std::string pass):_Password(pass)
{
	const int port = std::atoi(portStr.c_str());
	if (1 > port || port > 65535)
		throw IrcError("Error : port out of range 1-65536");
	_Port = static_cast<socket_t>(port);
}

Server::~Server() {}

const std::string	&Server::getPass() const
{
	return (_Password);
}

void	Server::socketInit()
{
	std::memset(&_SockAddr, 0, sizeof(_SockAddr));
	_SockAddr.sin_family = AF_INET;
	_SockAddr.sin_port = htons(_Port);
	_SockAddr.sin_addr.s_addr = inet_addr(INETADDR_ANY);

	if ((_Sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		throw IrcError("Error : socket creation");
    int reuse = 1;
    if (setsockopt(_Sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)) < 0)
		throw IrcError(strerror(errno));

#ifdef SO_REUSEPORT
    if (setsockopt(_Sock, SOL_SOCKET, SO_REUSEPORT, (const char*)&reuse, sizeof(reuse)) < 0) 
		throw IrcError(strerror(errno));
#endif
}

void	Server::setSocket()
{
	if (fcntl(_Sock, F_SETFL, O_NONBLOCK) < 0)
		throw IrcError(strerror(errno));
	if (bind(_Sock, reinterpret_cast<const sockaddr*>(&_SockAddr), sizeof(_SockAddr)) < 0)
		throw IrcError(strerror(errno));
	if (listen(_Sock, 100) < 0)
		throw IrcError(strerror(errno));
}

void	Server::checkEvents()
{
	char			buffer[4096];
	int				recvNChar = 0;
	pollvectorIter	it;
	commandList		commandList;
	int		i = 0;

	if (_PollVector.empty() || _PollVector.size() == 0)
		return ;
	it = _PollVector.begin();
	do
	{
		if (it->revents == POLLIN)
		{
			bzero(&buffer, 4095);
			recvNChar = recv(it->fd, &buffer, 4095, 0);
			if (recvNChar <= 0)
			{
				disconnectClient(it);
				return ;
			}
			_ClientMap[it->fd]->recvMessage(buffer);
			std::cout << YELLOW << "-----STARTING PARSING...-----" << std::endl;
			_ClientMap[it->fd]->parseMessage(commandList, it->fd);
			std::cout << GREEN << "-----PARSING DONE !-----" << std::endl;
			for (commandList::iterator itList = commandList.begin(); itList != commandList.end(); itList++)
			{
				std::cout << YELLOW << "-----STARTING EXEC...-----" << std::endl;
				std::cout << NC << "Original command = " << itList->originalCommand << '\n' << "nCommand = " << itList->command << '\n';
				if (itList->params.empty())
					std::cout << NC << "Empty param" << '\n';
				for (std::vector<std::string>::iterator it = itList->params.begin(); it != itList->params.end(); it++)
					std::cout << NC << "Param = " << *it << '\n';
				execCommand(*itList);
			}
			commandList.clear();
		}
		else if (it->revents == POLLHUP)
		{
			disconnectClient(it);
		}
		else if (it->revents == 17)
		{
			std::cout << RED << "Client unexpected deconnection" << NC << '\n';
			disconnectClient(it);
		}
		if (it != _PollVector.end())
			++it;
	} while (it != _PollVector.end());
}

void	Server::acceptConnection()
{
	struct sockaddr_in		client;
	socklen_t				clientSize = sizeof(sockaddr_in);
	struct pollfd			newPoll;
	int						clientFd = 0;

	memset(static_cast<void*>(&newPoll), 0, sizeof(newPoll));
	memset(static_cast<void*>(&client), 0, sizeof(client));
	while (ACCEPT_CLIENT)
	{
		clientFd = accept(_Sock, (sockaddr*)&client, &clientSize);
		if (clientFd < 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
			break;
		else if (clientFd < 0)
		{
			std::cout << RED << strerror(errno) << NC <<  '\n';
			return;
		}
		newPoll.fd = clientFd;
		newPoll.events = POLLIN;
		_PollVector.push_back(newPoll);
		clientNew(clientFd);
	}
}

void	Server::ConnectServer()
{
	socketInit();
	setSocket();
	while (RUNTIME)
	{
		poll(_PollVector.data(), _PollVector.size(), POLL_TIMEOUT);
		checkEvents();
		acceptConnection();
	}
	close(_Sock);
}
