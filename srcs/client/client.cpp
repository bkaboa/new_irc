#include "../../include/client/client.hpp"

using namespace irc;

Client::Client(fd_t fd):_Fd(fd), _IsConnect(false) {}

Client::Client():_IsConnect(false) {}

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

fd_t	Client::getFd() const {
	return (_Fd);
}

void	Client::setClient(const std::string &Nick, const std::string &Name, bool isConnect)
{
	_Nick = Nick;
	_Name = Name;
	_IsConnect = isConnect;
}
