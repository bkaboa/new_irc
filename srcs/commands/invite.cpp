#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

void Server::Invite(fd_t sender, std::vector<std::string> args)
{
	(void)sender;
	(void)args;
	std::cout << GREEN << "INVITE FUNCTION" << std::endl;
}