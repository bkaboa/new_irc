// #include "../../include/server/server.hpp"
// #include <sys/poll.h>
// #include <sys/socket.h>
// #include "../../include/IrcMessage/IrcMessage.hpp"

// using namespace irc;

// static std::vector<std::string> strSplit(const std::string &str, char separator)
// {
// 	std::vector<std::string> output;
// 	size_t prev_pos = 0, pos = 0;

// 	while ((pos = str.find(separator, pos)) != std::string::npos)
// 	{
// 		std::string substring(str.substr(prev_pos, pos - prev_pos));
// 		output.push_back(substring);
// 		prev_pos = ++pos;
// 	}
// 	output.push_back(str.substr(prev_pos, pos - prev_pos));
// 	return (output);
// }

// static bool isCommand(std::string str)
// {
// 	std::string tab[] = {"BAN", "INVITE", "JOIN", "KICK", "NICK", "PASS", "PRIVMSG", "TOPIC"};
// 	for (int i = 0; i < tab->size(); i++)
// 		if (str == tab[i])
// 			return (true);
// 	return (false);
// }

// // without prefix for now : Example message : JOIN #channel //// or PRIVSMSG #channel :Hello guys
// void IrcMessage::parseMessage(std::string message, fd_t target)
// {
// 	std::vector<std::string> tab = strSplit(message, ' ');
// 	if (isCommand(tab[0]))
// 	{
// 		this->setCommand(tab[0]);
// 	}
// }