#include "include/server/server.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << RED << "Need 2 argument for irc ./\"exec\" \"port\" and \"password\"" << NC << std::endl;
		return (1);
	}
	try {
		irc::Server ircServer(argv[1], argv[2]);
		ircServer.ConnectServer();
	} catch (const std::exception &e) {
		std::cout << RED << e.what() << NC << std::endl;
		return (1);
	}
	return (0);
}
