#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

void Server::Quit(fd_t sender, std::list<struct paramsData_t> args)
{
	(void)sender;
	(void)args;
	std::cout << GREEN << "QUIT FUNCTION" << std::endl;
}