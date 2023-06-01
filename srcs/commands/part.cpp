#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

void Server::Part(fd_t sender, const commandData_t &args)
{
	if (args.binParams == NONE || !(args.binParams & CHAN))
		sendStr(sender, ERR_NEEDMOREPARAMS(_ClientMap[sender]->getNick(), "PART"));
	std::string reason;
	if (args.binParams & MESS)
		reason = args.params[2];
	std::vector<std::string> channelsToPart;
	channelsToPart = strSplit(args.params[1], ',');

	for (std::vector<std::string>::iterator itera = channelsToPart.begin(); itera != channelsToPart.end(); ++itera)
	{
		std::cout << "PART channels ---" << *itera << std::endl;
	}
}