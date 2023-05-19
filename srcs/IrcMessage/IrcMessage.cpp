#include "../../include/server/server.hpp"
#include <sys/poll.h>
#include <sys/socket.h>
#include <../../include/IrcMessage/IrcMessage.hpp>

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

// void Server::sndMessage(std::string message, fd_t target)
// {
// 	//sends a message to the corresponding fd
// }

//without prefix for now : Example message : JOIN #channel //// or PRIVSMSG #channel :Hello guys
void parseMessage(std::string message, fd_t target)
{
	std::vector<std::string> tab = strSplit(message, ' ');
	
}

int main(int ac, char **av)
{
	std::string fullmsg;
	av = &av[1];
	for (int i = 0; av[i]; i++)
	{
		fullmsg.append(av[i]);
		if (av[i + 1])
			fullmsg.append(" ");
	}
	std::cout << fullmsg << std::endl;
}