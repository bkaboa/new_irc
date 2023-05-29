// #include "../../include/include.hpp"
// #include "../../include/IrcMessage/IrcMessage.hpp"
// #include "../../include/server/server.hpp"
// #include "../../include/client/client.hpp"

using namespace irc;

void Server::Privmsg(fd_t sender, std::vector<std::string> args)
{
	(void)sender;
	(void)args;
	std::cout << GREEN << "Privmsg FUNCTION" << std::endl;
}
