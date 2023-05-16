#include "../../include/server/server.hpp"
#include <sys/poll.h>
#include <sys/socket.h>

using namespace irc;

static std::vector<std::string> strSplit(const std::string &str, char separator)
{
	std::vector<std::string> output;
	size_t prev_pos = 0, pos = 0;

	while((pos = str.find(separator, pos)) != std::string::npos)
	{
		std::string substring(str.substr(prev_pos, pos - prev_pos));
		output.push_back(substring);
		prev_pos = ++pos;
	}
	output.push_back(str.substr(prev_pos, pos - prev_pos));
	return(output);
}

//!!!PROTOCODE!!!
int Server::command(std::string command)
{
	void (Server::*ptr_func[8])(void) = {&Server::ban, &Server::invite, &Server::join \
	, &Server::kick, &Server::nick, &Server::pass, &Server::privmsg, &Server::topic};
	std::string commands[8] = {"ban", "invite", "join", "kick", "nick", "pass", "privmsg", "topic"};
	for (int i = 0; i < 8; i++)
	{
		if (command == commands[i])
		{
			(*this->ptr_func[i]());
			return;
		}
	}
}
//!!!PROTOCODE!!!


void Server::sndMessage(std::string message, fd_t fd)
{
	//sends a message to the corresponding fd
}

void Server::parseMessage(std::string message, fd_t fd)
{
	std::vector<std::string> tab = strSplit(message, ' ');
	if (tab[0].at(0) != '/')
	{
		sndMessage(message, fd);
		return;
	}

}
