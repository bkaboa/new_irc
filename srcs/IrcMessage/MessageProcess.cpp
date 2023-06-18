#include "../../include/server/server.hpp"
#include "../../include/IrcMessage/IrcMessage.hpp"

using namespace irc;

typedef void (Server::*FunctionPointer)(fd_t, const struct commandData_t &);

void Server::execCommand(commandData_t &cmd)
{
	if (cmd.command == -1)
		return;
	FunctionPointer functions[12] = { &Server::Invite, &Server::Join, &Server::Kick, &Server::Mode, \
									  &Server::Nick, &Server::Part, &Server::Pass, &Server::Privmsg, &Server::Quit, \
									  &Server::Topic, &Server::User, &Server::Notice};
	binParamDisplay(cmd.binParams);
	(this->*(functions[cmd.command]))(cmd.clientRequest, cmd);
}
