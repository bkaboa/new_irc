#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

void Server::List(fd_t sender, std::vector<std::string> args)
{
	(void)sender;
	(void)args;
	std::cout << GREEN << "LIST FUNCTION" << std::endl;
}