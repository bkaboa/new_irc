#include "../../include/IrcMessage/IrcMessage.hpp"

using namespace irc;

IrcMessage::IrcMessage() {}

IrcMessage::~IrcMessage() {}

void	IrcMessage::recvMessage(const std::string &message)
{
	std::string		endMessage = "\r\n";

	_Message.append(message);
	std::cout << _Message << '\n';
	if ((message.end() - 2).base() == endMessage)
		_MessageCompleted = true;
}

void	IrcMessage::parseMessage()
{
}
