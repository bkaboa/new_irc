#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

void Server::Join(fd_t sender, const commandData_t &args)
{
	(void)sender;
	(void)args;
	std::cout << GREEN << "JOIN FUNCTION" << std::endl;
}