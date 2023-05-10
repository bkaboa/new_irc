#pragma once

#include "include.hpp"
#include "define.hpp"

namespace irc
{
	class IrcError : virtual public std::exception
	{
		public:
			IrcError(std::string msg):_Message(msg) {}
			virtual ~IrcError() throw() {};
			virtual const char* what() const throw()
			{
				return (_Message.c_str());
			}
		private:
			std::string	_Message;
	};
}
