#include "../../include/IrcMessage/IrcMessage.hpp"
#include <limits>
#include <strings.h>

using namespace irc;

IrcMessage::IrcMessage() {}

IrcMessage::~IrcMessage() {}

void	IrcMessage::recvMessage(const std::string &message)
{
	std::string		endMessage = "\r\n";

	_Message = message;
	if (_Message.size() > 512)
	{
		_Message.clear();
	}
	if ((message.end() - 2).base() == endMessage)
			_Message.erase(_Message.end() - 2, _Message.end());
}

void	IrcMessage::stringSlice(size_t nPos, std::string &original, std::string &sliced)
{
	std::string	tmp;

	if (nPos == std::string::npos || nPos == original.size())
	{
		sliced = original.substr();
		original.clear();
	}
	else
	{
		sliced = original.substr(0, nPos);
		tmp = original.substr(nPos);
		original.clear();
		original = tmp;
	}
}

struct commandData_t IrcMessage::parseMessage()
{
	struct commandData_t	command;
	int						newLinePos = _Message.find_first_of('\n');
	std::string				sliceMessage;

	bzero(&command, sizeof(struct commandData_t));
	command.clientRequest = _ClientRequest;
	if (_Message.empty())
		return (command);
	while (newLinePos <= 3 && newLinePos != std::string::npos)
	{
		_Message.erase(0, newLinePos + 1);
		newLinePos = _Message.find_first_of('\n');
	}
	if (newLinePos != std::string::npos)
	{
		stringSlice(newLinePos + 1, _Message, sliceMessage);
		parseMessage();
	}
	command.originalCommand = sliceMessage.substr();
	command.command = checkCommand(sliceMessage, &command.binParams);
	if (command.command != 0)
	{
		if (CHAN & command.binParams)
			takeParams(&command, sliceMessage, CHAN);
		if (NICK & command.binParams)
			takeParams(&command, sliceMessage, NICK);
		if (PASS & command.binParams)
			takeParams(&command, sliceMessage, PASS);
		if (MESS & command.binParams)
			takeMessage(&command, sliceMessage);
		if (USER & command.binParams)
			takeParams(&command, sliceMessage, USER);
		if (TARG & command.binParams)
			takeParams(&command, sliceMessage, TARG);
	}
	return (command);
}

int BAN(const std::string& s) { return BAN_MACRO(s); }
int INVITE(const std::string& s) { return INVITE_MACRO(s); }
int JOIN(const std::string& s) { return JOIN_MACRO(s); }
int KICK(const std::string& s) { return KICK_MACRO(s); }
int LIST(const std::string& s) { return LIST_MACRO(s); }
int NICKC(const std::string& s) { return NICK_MACRO(s); }
int PART(const std::string& s) { return PART_MACRO(s); }
int PASSC(const std::string& s) { return PASS_MACRO(s); }
int PRIVMSG(const std::string& s) { return PRIVMSG_MACRO(s); }
int QUIT(const std::string& s) { return QUIT_MACRO(s); }
int TOPIC(const std::string& s) { return TOPIC_MACRO(s); }
int USERC(const std::string& s) { return USER_MACRO(s); }
int CAP(const std::string& s) { return CAP_MACRO(s); }

int	IrcMessage::checkCommand(std::string &sentence, int *binParams)
{
	int			result;
    using macroFunction = int (*)(const std::string&);
	std::string word;

    macroFunction macros[] = {
        BAN,
        INVITE,
        JOIN,
        KICK,
        LIST,
        NICKC,
        PART,
        PASSC,
        PRIVMSG,
        QUIT,
        TOPIC,
        USERC,
        CAP
    };
	result = sentence.find_first_of(" \n");
	if (result == std::string::npos)
		word = sentence;
	else
		stringSlice(result, sentence, word);
	if (word.empty() || word.size() <= 2)
		return (0);
	for(int i = 0; i < 13; i++)
	{
		if ((result = macros[i](word)) != 0)
		{
			*binParams = result;
			return (i);
		}
	}
	return (0);
}

void	IrcMessage::takeParams(struct commandData_t *command, std::string &sliceMessage, int params)
{
	int			npos = sliceMessage.find_first_of(" \n\r");
	std::string param;

	stringSlice(npos, sliceMessage, param);
	if (param.empty() || param.size() == 0)
	{
		command->binParams -= params;
		return;
	}
	command->params.push_back(param);
}

void	IrcMessage::takeMessage(struct commandData_t *command, std::string &sliceMessage)
{
	int			npos = sliceMessage.find_first_of("\n\r");
	std::string param;

	stringSlice(npos, sliceMessage, param);
	if (param.empty() || param.size() == 0)
	{
		command->binParams -= MESS;
		return;
	}
	command->params.push_back(param);
}
