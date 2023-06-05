#include "../../include/channel/channel.hpp"
#include "../../include/client/client.hpp"
#include "../../include/server/server.hpp"


using namespace irc;

Channel::Channel(Client *creator, const std::string &name, const std::string &pass):_Name(name), _Password(pass), _Topic(""){
	_Members.insert(std::make_pair(creator->getFd(), creator));
};

Channel::~Channel() {};

const std::string	&Channel::getName() const {
	return (_Name);
}

bool	Channel::checkBan(fd_t clientFd) {
	vectorFdClientIter vIter = _FdClientBanned.begin();

	for (;vIter != _FdClientBanned.end(); vIter++)
	{
		if (clientFd == *vIter.base())
			return (false);
	}
	return (true);
}

void	Channel::addMember(Client *newMember, bool admin)
{
	if (_Members.find(newMember->getFd()) != _Members.end())
	{
		std::cout << "client " << newMember->getNick() << " is already connected to the channel _Name" << std::endl;
	}
	else
	{
		if (admin == true)
			_FdAdmin.push_back(newMember->getFd());
		_Members.insert(std::make_pair(newMember->getFd(), newMember));
	}
}

void	Channel::removeMember(fd_t clientFd)
{
	if (_Members.find(clientFd) != _Members.end())
	{
		_Members.erase(clientFd);
	}
	else
	{
		std::cout << "Member is not on channel " << _Name << std::endl;
	}
}

bool	Channel::checkPass(std::string pass)
{
	if (pass.compare(_Password) != 0)
		return (false);
	return(true);
}

std::string Channel::getPass(void)
{
	return (_Password);
}

void	Channel::setAdmin(fd_t newAdminFd)
{
	if (_Members.find(newAdminFd) == _Members.end())
		std::cout << "client doesn't in the channel " << _Name << std::endl;
	else
		_FdAdmin.push_back(newAdminFd);
}

void	Channel::kickMember(fd_t fd)
{
}

void	Channel::channelMsg(std::string msg)
{
	if (!msg.empty())
	{
		mapClientIter iter;
		for (iter = _Members.begin(); iter != _Members.end(); ++iter)
		{
			if (!checkBan(iter->first))
				sendStr(iter->first, msg);
		}
	}
}

bool Channel::isInChannel(fd_t clientFd)
{
	mapClientIter iter = _Members.find(clientFd);
	if (iter == _Members.end())
		return(false);
	return (true);
}

std::string	Channel::getName(void)
{
	return (_Name);
}

void	Channel::setTopic(std::string topic)
{
	_Topic = topic;
}

const std::string	Channel::getTopic()
{
	return(_Topic);
}