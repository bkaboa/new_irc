#include "../../include/client/client.hpp"

using namespace irc;

Client::Client(fd_t fd):_Fd(fd), _IsRegistered(false) , _passOk(false), _nickOk(false){}

Client::Client():_IsRegistered(false) {}

Client::~Client() {}

const std::string	&Client::getNick() const
{
	return (_Nick);
}

const std::string	&Client::getName() const
{
	return (_Name);
}

bool	Client::isRegistered() const
{
	return (_IsRegistered);
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
	_IsRegistered = isConnect;
}

void	Client::setIsRegistered(bool truefalse)
{
	if (!truefalse)
		this->_IsRegistered = false;
	else if (truefalse)
		this->_IsRegistered = true;
}

bool	Client::getPassOk(void)
{
	return(_passOk);
}

bool	Client::getNickOk(void)
{
	return(_nickOk);
}

void	Client::setPassOk(bool truefalse)
{
	_passOk = truefalse;
}

void	Client::setNickOk(bool truefalse)
{
	_nickOk = truefalse;
}
