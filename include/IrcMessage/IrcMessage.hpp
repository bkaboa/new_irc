#ifndef IRCMESSAGE_HPP
#define IRCMESSAGE_HPP

#include "../include.hpp"
#include "../define.hpp"
#include "../typedef.hpp"
#include "../error.hpp"

class IrcMessage
{
	private:
		std::string _command;
		std::string _message;
		std::vector<std::string> _params;
	public:
		IrcMessage();
		~IrcMessage();
};

#endif