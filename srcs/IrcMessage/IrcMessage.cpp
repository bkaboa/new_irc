#include "../../include/IrcMessage/IrcMessage.hpp"
#include <cctype>
#include <string>
#include <strings.h>

using namespace irc;

IrcMessage::IrcMessage() {}

IrcMessage::~IrcMessage() {}

void	IrcMessage::recvMessage(std::string message)
{
	std::string		endMessage = "\r\n";

	if (message.size() > 512 || message.size() < 3)
	{
		message.clear();
		return ;
	}
	if ((message.end() - 2).base() == endMessage)
			message.erase(message.end() - 2, message.end());
	_Message = message;
}

bool	IrcMessage::stringSlice(size_t nPos, std::string &original, std::string &sliced)
{
	std::string	tmp;

	if (original.empty() || original.size() == 0 || nPos == 0)
		return (false);
	if (nPos == std::string::npos || nPos == original.size())
	{
		sliced = original.substr();
		original.clear();
		return (true);
	}
	else
	{
		sliced = original.substr(0, nPos);
		tmp = original.substr(nPos + 1);
		original.clear();
		original = tmp;
	}
	return (true);
}

void IrcMessage::parseMessage(commandList &commandList, fd_t fd)
{
	struct commandData_t		command;
	std::vector<std::string>	commands;
	std::vector<std::string>	params;
	std::string					tmp;
	size_t						nPos = 0;

	if (_Message.empty())
		return ;
	while (stringSlice(_Message.find_first_of('\n'), _Message, tmp))
	{
		commands.push_back(tmp);
	}
	for (std::vector<std::string>::iterator it = commands.begin(); it != commands.end(); it++)
	{
		bzero(&command, sizeof(command));
		command.clientRequest = fd;
		if (it->empty() || it->size() < 3)
			commandList.push_back(command);
		else
		{
			command.originalCommand = *it;
			checkCommand(*it, &command.binParams, &command.command);
			if (command.binParams & CHAN)
				takeChannel(&command, *it);
			if (command.binParams & NICK)
				takeNick(&command, *it);
			if (command.binParams & TARG)
				takeTarget(&command, *it);
			if (command.binParams & PASS)
				takePass(&command, *it);
			if (command.binParams & MESS)
				takeMessage(&command, *it);
			if (command.binParams & USER)
				takeUser(&command, *it);
			commandList.push_back(command);
		}
	}
	_Message.clear();
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
	*command = -1;
	stringSlice(sentence.find_first_of(" \n"), sentence, word);
	std::cout << NC << "command =" << word <<'|'<< '\n';
	if (word.empty() || word.size() <= 3)
		return ;
	for(int i = 0; i < 13; i++)
	{
		if ((result = macros[i](word)) != 0)
		{
			*binParams = result;
			*command = i;
			return;
		}
	}
}

void	IrcMessage::takeUser(struct commandData_t *command, std::string &sliceMessage)
{
	std::istringstream	istring;
	std::string			user;

	if (!std::isalnum(sliceMessage[0]))
	{
		command->binParams -= USER;
		return;
	}
	if (sliceMessage.empty() || sliceMessage.size() == 0)
	{
		command->binParams -= USER;
		return;
	}
	istring.str(sliceMessage);
	while (std::getline(istring, user, ' '))
	{
		command->params.push_back(user);
	}
}

void	IrcMessage::takeChannel(struct commandData_t *command, std::string &sliceMessage)
{
	std::string			channel;

	std::cout << "chan = " << sliceMessage << '\n';
	if (sliceMessage[0] != '#')
	{
		command->binParams -= CHAN;
		return ;
	}
	stringSlice(sliceMessage.find_first_of(" \r\n"), sliceMessage, channel);
	if (channel.empty() || channel.size() == 0)
	{
		command->binParams -= CHAN;
		return ;
	}
	command->params.push_back(channel);
}

void	IrcMessage::takeNick(struct commandData_t *command, std::string &sliceMessage)
{
	int					npos = sliceMessage.find_first_of(" \r\n");
	std::string			nick;

	if (!std::isalnum(sliceMessage[0]))
	{
		command->binParams -= NICK;
		return ;
	}
	stringSlice(npos, sliceMessage, nick);
	if (nick.empty() || nick.size() == 0)
	{
		command->binParams -= NICK;
		return ;
	}
	command->params.push_back(nick);
}

void	IrcMessage::takeTarget(struct commandData_t *command, std::string &sliceMessage)
{
	std::string param;

	if (!std::isalnum(sliceMessage[0]) && sliceMessage[0] != '#')
	{
		command -= PASS;
		return;
	}
	stringSlice(sliceMessage.find_first_of(" \r\n"), sliceMessage, param);
	if (param.empty() || param.size() == 0)
	{
		command->binParams -= PASS;
		return;
	}
	command->params.push_back(param);
}

void	IrcMessage::takeMessage(struct commandData_t *command, std::string &sliceMessage)
{
	std::string param;

	if (sliceMessage[0] != ':')
	{
		command->binParams -= MESS;
		return;
	}
	stringSlice(sliceMessage.find_first_of("\r\n"), sliceMessage, param);
	if (param.empty() || param.size() == 0)
	{
		command->binParams -= MESS;
		return;
	}
	command->params.push_back(param);
}

void	IrcMessage::takePass(struct commandData_t *command, std::string &sliceMessage)
{
	std::string param;

	if (!(std::isalnum(sliceMessage[0])))
	{
		command->binParams -= PASS;
		return;
	}
	stringSlice(sliceMessage.find_first_of("\r\n"), sliceMessage, param);
	if (param.empty() || param.size() == 0)
	{
		command->binParams -= PASS;
		return;
	}
	command->params.push_back(param);
}
