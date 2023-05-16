#include "../../include/server/server.hpp"

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
	char		buffer[512];
	int			recvNChar = 0, tmp = 0;
	std::string message;

	if (_PollVector.empty())
		return ;
	for (pollvectorIter it = _PollVector.begin(); it != _PollVector.end(); it++)
	{
		if (it->revents == POLLIN)
		{
			do
			{
				bzero(&buffer, sizeof(buffer));
				recvNChar = recv(it->fd, &buffer, sizeof(buffer), MSG_PEEK | MSG_DONTWAIT);
				recvNChar += tmp;
				message.append(buffer);
				tmp = recvNChar;
			} while (message[recvNChar] != '\n');
		}
		if (it->revents == POLLHUP)
		{
			disconnectClient(it->fd);
		}
	}
}

void	Server::acceptConnection()
{
	struct sockaddr_in		client;
	socklen_t				clientSize = sizeof(sockaddr_in);
	struct pollfd			newPoll;
	fd_t					clientFd = 0;

	memset(static_cast<void*>(&newPoll), 0, sizeof(newPoll));
	memset(static_cast<void*>(&client), 0, sizeof(client));
	while (ACCEPT_CLIENT)
	{
		clientFd = accept(_Sock, (sockaddr*)&client, &clientSize);
		if (clientFd < 0 && (errno == EAGAIN || errno == EWOULDBLOCK))
			break;
		else if (clientFd < 0)
			std::cout << RED << strerror(errno) << NC <<  '\n';
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
		acceptConnection();
		checkEvents();
	}
	close(_Sock);
}
