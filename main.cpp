#include "include/server/server.hpp"
#include "include/define.hpp"
#include <csignal>

int globalRuntime;
void	signalHandler(int sig)
{
	if (sig == SIGINT)
		globalRuntime = 0;
}

int main(int argc, char **argv)
{
	globalRuntime = 1;
	if (argc != 3)
	{
		std::cout << RED << "Need 2 argument for irc ./\"exec\" \"port\" and \"password\"" << NC << std::endl;
		return (1);
	}
	try {
		std::signal(SIGINT, &signalHandler);
		irc::Server ircServer(argv[1], argv[2]);
		ircServer.ConnectServer();
	} catch (const std::exception &e) {
		std::cout << RED << e.what() << NC << std::endl;
		return (1);
	}
	return (0);
}
