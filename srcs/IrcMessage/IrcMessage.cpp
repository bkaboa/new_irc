#include "../../include/IrcMessage/IrcMessage.hpp"

using namespace irc;

IrcMessage::IrcMessage() {}

IrcMessage::~IrcMessage() {}

void	IrcMessage::recvMessage(const std::string &message)
{
	std::string		endMessage = "\r\n";
	static bool		tooLong = false;

	if (tooLong == false)
		_Message.append(message);
	if (_Message.size() > 512)
	{
		tooLong = true;
		_Message.erase();
	}
	if ((message.end() - 2).base() == endMessage)
	{
		if (tooLong == false)
			_MessageCompleted = true;
		tooLong = false;
	}
}

void	IrcMessage::parseMessage()
{
	if (_MessageCompleted == false)
		return ;
	_MessageCompleted = false;
	
}
