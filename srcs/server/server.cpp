#include "../../include/server/server.hpp"
#include <sys/poll.h>
#include <sys/socket.h>

using namespace irc;

Server::Server(std::string portStr, std::string pass):_Password(pass)
{
	const int port = std::atoi(portStr.c_str());
	if (1 > port || port > 65535)
		throw IrcError("Error : port out of range 1-65536");
	_Port = static_cast<socket_t>(port);
}

Server::~Server() {}

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
	std::string		recvMessage;
	ssize_t			recvNChar = 0;
	if (_PollVector.empty())
		return ;
	for (pollvectorIter it = _PollVector.begin(); it != _PollVector.end(); it++)
	{
		if (it->revents == POLLIN)
		{
			do
			{
			} while (recvMessage[recvNChar] != '\n');
		}
		if (it->revents == POLLHUP)
		{
		}
	}
}

const std::string		&Server::getPass() const
{
	return (_Password);
}

// void	Server::acceptClient()
// {
// 	Client	newClient;
// 	while (ACCEPT_CLIENT)
// 	{
// 		accept(_Sock, struct sockaddr *, socklen_t *)
// 	}
// }

void	Server::ConnectServer()
{
	socketInit();
	setSocket();
	while (RUNTIME)
	{
		poll(_PollVector.data(), _PollVector.size(), POLL_TIMEOUT);
		checkEvents();
	}
	close(_Sock);
}
