#include "../../include/IrcMessage/IrcMessage.hpp"
#include <strings.h>

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

struct messageData_t	IrcMessage::parseMessage()
{
	struct messageData_t	messageData;

	bzero(&messageData, sizeof(struct messageData_t));
	if (_MessageCompleted == false)
		return (messageData);
	_MessageCompleted = false;

	return (messageData);
}

void	IrcMessage::checkCommand(const std::string &commandName)
{
	int		i = 0;

	//while ()
}
