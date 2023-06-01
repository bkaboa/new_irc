#include "../../include/IrcMessage/IrcMessage.hpp"
#include <string>
#include <strings.h>

using namespace irc;

IrcMessage::IrcMessage() {}

IrcMessage::~IrcMessage() {}

void	IrcMessage::recvMessage(std::string &message)
{
	std::string		endMessage = "\r\n";

	if (message.size() > 512 || message.size() < 3)
	{
		message.clear();
		return ;
	}
	if ((message.end() - 2).base() == endMessage)
			message.erase(message.end() - 2, message.end());
	_Message.str(message);
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

void IrcMessage::parseMessage(commandList &commandList)
{
	struct commandData_t		command;
	std::vector<std::string>	commands;
	std::vector<std::string>	params;
	std::string					tmp;
	size_t						nPos = 0;

	if (_Message.str().empty())
		return ;
	while (std::getline(_Message, tmp, '\n'))
		commands.push_back(tmp);
	for (std::vector<std::string>::iterator it = commands.begin(); it != commands.end(); it++)
	{
		bzero(&command, sizeof(command));
		if (it->empty() || it->size() < 3)
			commandList.push_back(command);
		else
		{
			checkCommand(*it, &command.binParams, &command.command);
			if (command.binParams & CHAN)
				takeChannel(&command, *it);
			if (command.binParams & NICK)
				takeNick(&command, *it);
			if (command.binParams & TARG)
				takeParams(&command, *it, TARG);
			if (command.binParams & PASS)
				takeParams(&command, *it, PASS);
			if (command.binParams & MESS)
				takeMessage(&command, *it);
			if (command.binParams & USER)
				takeUser(&command, *it);
			commandList.push_back(command);
		}
	}
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

void	IrcMessage::checkCommand(std::string &sentence, int *binParams, int *command)
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
	if (word.empty() || word.size() <= 3)
		return ;
	for(int i = 0; i < 13; i++)
	{
		if ((result = macros[i](word)) != 0)
		{
			*binParams = result;
			*command = i;
		}
	}
	*command = i;
}

void	IrcMessage::takeUser(struct commandData_t *command, std::string &sliceMessage)
{
	std::istringstream	istring;
	std::string			user;

	if (sliceMessage.empty() || sliceMessage.size() == 0)
	{
		command->binParams -= USER;
		return;
	}
	istring.str(sliceMessage);
	while (std::getline(istring, user, ' '))
	{
		std::cout << user << '\n';
		command->params.push_back(user);
	}
}

void	IrcMessage::takeChannel(struct commandData_t *command, std::string &sliceMessage)
{
	int					npos = sliceMessage.find_first_of(" \n\r");
	std::istringstream	istring;
	std::string			channel;

	stringSlice(npos, sliceMessage, channel);
	if (channel.empty() || channel.size() == 0)
	{
		command->binParams -= CHAN;
		return ;
	}
	istring.str(channel);
	while (std::getline(istring, channel, ','))
	{
		std::cout << channel << '\n';
		command->params.push_back(channel);
	}
}

void	IrcMessage::takeNick(struct commandData_t *command, std::string &sliceMessage)
{
	int					npos = sliceMessage.find_first_of(" \n\r");
	std::istringstream	istring;
	std::string			nick;

	stringSlice(npos, sliceMessage, nick);
	if (nick.empty() || nick.size() == 0)
	{
		command->binParams -= NICK;
		return ;
	}
	istring.str(nick);
	while (std::getline(istring, nick, ','))
	{
		std::cout << nick << '\n';
		command->params.push_back(nick);
	}
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
