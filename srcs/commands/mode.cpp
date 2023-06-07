#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

void Server::Mode(fd_t sender, const commandData_t &args)
{
	std::cout << NC << "Client with fd " << sender << " requested a Mode command" << std::endl;

	(void)sender;
	(void)args;
}