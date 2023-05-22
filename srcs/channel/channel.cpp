#include "../../include/channel/channel.hpp"

using namespace irc;

Channel::Channel() {};

Channel::~Channel() {};

const std::string	&Channel::getName() const {
	return (_Name);
}

bool	Channel::checkBan(std::string name) {
	if ()
}
