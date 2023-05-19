#include "../../include/client/client.hpp"

using namespace irc;

Client::Client(fd_t fd):_Fd(fd) {}

Client::~Client() {}

const std::string	&Client::getNick() const
{
	return (_Nick);
}

const std::string	&Client::getName() const
{
	return (_Name);
}

bool	Client::isConnect() const
{
	return (_IsConnect);
}

void	Client::changeName(const std::string &name)
{
	_Name = name;
}

void	Client::changeNick(const std::string &nick)
{
	_Nick = nick;
}
