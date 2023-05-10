#include "include/include.hpp"
#include "include/server/server.hpp"
#include "include/define.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "need 2 argument for irc ./\"exec\" \"port\" and \"password\"" << std::endl;
		return (1);
	}
	try {
		irc::Server ircServer(argv[1], argv[2]);
		ircServer.ConnectServer();
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
		return (1);
	}
	return (0);
}
