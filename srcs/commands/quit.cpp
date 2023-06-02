#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

void Server::Quit(fd_t sender, const commandData_t &args)
{
	(void)sender;
	(void)args;
}