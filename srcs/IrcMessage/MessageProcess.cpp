#include "../../include/server/server.hpp"
#include <sys/poll.h>
#include <sys/socket.h>
#include "../../include/IrcMessage/IrcMessage.hpp"

using namespace irc;

typedef void (Server::*FunctionPointer)(fd_t, std::vector<std::string>);

void Server::execCommand(messageData_t &command)
{
	FunctionPointer functions[12] = { &Server::Ban, &Server::Invite, &Server::Invite, &Server::Invite, &Server::Invite , \
									  &Server::Invite, &Server::Invite, &Server::Invite, &Server::Invite, &Server::Invite, \
									  &Server::Invite, &Server::Invite };
}
