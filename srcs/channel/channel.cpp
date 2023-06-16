#include "../../include/channel/channel.hpp"
#include "../../include/client/client.hpp"
#include "../../include/server/server.hpp"


using namespace irc;

Channel::Channel(Client *creator, const std::string &name, const std::string &pass):_Password(pass), _Name(name), _Topic(""), _ChannelOptions(0), _userLimit(0){
	_Members.insert(std::make_pair(creator->getFd(), creator));
	if (!_Password.empty())
		_ChannelOptions += k;
	setAdmin(creator->getFd(), true);
};

Channel::~Channel() {};

const std::string	&Channel::getName() const {
	return (_Name);
}

void	Channel::addMember(Client *newMember, bool admin)
{
	if (_Members.find(newMember->getFd()) != _Members.end())
	{
		std::cout << "Client " << newMember->getNick() << " is already connected to the channel _Name" << std::endl;
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

void	Channel::setAdmin(fd_t newAdminFd, bool truefalse)
{
	if (_Members.find(newAdminFd) == _Members.end())
		std::cout << "Client is not in the channel " << _Name << std::endl;
	else
	{
		if (truefalse && !isAdmin(newAdminFd))
		{
			_FdAdmin.push_back(newAdminFd);
			return;
		}
		else if (!truefalse)
		{
			std::vector<fd_t>::iterator iter = _FdAdmin.begin();
			for(; iter != _FdAdmin.end(); ++iter)
			{
				if (*iter == newAdminFd)
				{
					_FdAdmin.erase(iter);
					return;
				}	
			}
		}
	}
}

void	Channel::setPassword(std::string pass)
{
	if (pass.empty())
		_Password.clear();
	_Password = pass;
}

void	Channel::setUserLimit(int limit)
{
	_userLimit = limit;
}

int		Channel::getUserLimit(void)
{
	return (_userLimit);
}

bool	Channel::isAdmin(fd_t clientfd)
{
	std::vector<fd_t>::iterator iter = _FdAdmin.begin();
	for (; iter != _FdAdmin.end(); ++iter)
	{
		if (*iter == clientfd)
			return (true);
	}
	return(false);
}

void	Channel::kickMember(fd_t kicked)
{
	if (!isAdmin(kicked))
		_Members.erase(kicked);
}

void	Channel::channelMsg(fd_t sender, std::string msg)
{
	mapClientIter iter;
	for (iter = _Members.begin(); iter != _Members.end(); ++iter)
	{
		//SEND TO ALL MEMBERS
		if (sender == -1)
			sendStr(iter->first, msg);
		//SEND TO ALL EXCEPT SENDER
		else
		{
			if (iter->first != sender)
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

int	Channel::getNumClients(void)
{
	return (_Members.size());
}

void	Channel::setTopic(std::string topic)
{
	_Topic = topic;
}

const std::string	Channel::getTopic()
{
	return(_Topic);
}

void	Channel::joinNameReply(fd_t sender, std::string sendername)
{
	mapClientIter iter;
	iter = _Members.begin();
	if (!(getTopic().empty()))
		sendStr(sender, RPL_TOPIC(iter->second->getNick(), getName(), getTopic()));
	for (; iter != _Members.end(); ++iter)
	{
		if (isAdmin(iter->first))
			sendStr(sender, RPL_NAMREPLY(iter->second->getName(), "!", _Name, "@", iter->second->getNick(), ""));
		else
			sendStr(sender, RPL_NAMREPLY(iter->second->getName(), "!", _Name, " ", iter->second->getNick(), ""));
	}
	sendStr(sender, RPL_ENDOFNAMES(sendername, _Name));
}

void	Channel::setOptions(u_int8_t mode, int sign)
{
	if (sign)
		_ChannelOptions += mode;
	else if (!sign)
		_ChannelOptions -= mode;
}

u_int8_t Channel::getOptions()
{
	return (_ChannelOptions);
}

void	Channel::addInvite(fd_t invited)
{
	std::vector<fd_t>::iterator iter = _Invited.begin();
	for (; iter != _Invited.end(); ++iter)
	{
		if (*iter == invited)
			return;
	}
	_Invited.push_back(invited);
}

void	Channel::removeInvite(fd_t toremove)
{
	std::vector<fd_t>::iterator iter = _Invited.begin();
	for (; iter != _Invited.end(); ++iter)
	{
		std::cout << YELLOW << "fd : " << toremove << std::endl;
		std::cout << YELLOW << "iter : " << *iter << std::endl;
		if (*iter == toremove)
		{
			_Invited.erase(iter);
			return;
		}	
	}
	return;
}

void	Channel::clearInvite()
{
	_Invited.clear();
}

bool	Channel::isInvited(fd_t clientFd)
{
	std::vector<fd_t>::iterator iter = _Invited.begin();
	for (; iter != _Invited.end(); ++iter)
	{
		if (*iter == clientFd)
			return(true);
	}
	return(false);
}
