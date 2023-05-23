#include "../../include/channel/channel.hpp"

using namespace irc;

Channel::Channel() {};

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
