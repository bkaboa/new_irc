#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../include.hpp"
#include "../define.hpp"
#include "../typedef.hpp"
#include "../error.hpp"

namespace irc
{
	class Channel
	{
	private:
		std::string _name;
		std::string _topic;
		channelMembers _members;
	public:
		Channel();
		addClient();
		~Channel();
	};

}


#endif