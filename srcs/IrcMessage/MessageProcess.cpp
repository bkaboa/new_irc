#include "../../include/server/server.hpp"
#include <sys/poll.h>
#include <sys/socket.h>
#include "../../include/IrcMessage/IrcMessage.hpp"

using namespace irc;

void Server::processMessage(fd_t sender, char *message)
{
	std::string request(message);
	std::vector<std::string> requestTab;
	// requestTab = strSplit(request, ' ');
	// std::cout << "Beginning for loop" << std::endl;
	// for(int i = 0; !requestTab[i].empty(); i++)
	// 	std::cout << YELLOW << requestTab[i] << std::endl;
}
