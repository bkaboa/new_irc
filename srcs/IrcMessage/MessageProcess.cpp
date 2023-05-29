#include "../../include/server/server.hpp"
#include "../../include/IrcMessage/IrcMessage.hpp"

using namespace irc;

typedef void (Server::*FunctionPointer)(fd_t, std::list<struct paramsData_t>);

void Server::execCommand(commandData_t &cmd)
{
	FunctionPointer functions[12] = { &Server::Ban, &Server::Invite, &Server::Join, &Server::Kick, &Server::List , \
									  &Server::Nick, &Server::Part, &Server::Pass, &Server::Privmsg, &Server::Quit, \
									  &Server::Topic, &Server::User};
	(this->*(functions[cmd.command]))(cmd.clientRequest, cmd.params);
}
