#include "../../include/include.hpp"

void	sendStr(std::string str, fd_t clientFd)
{
	const char *tosend = str.c_str();
	size_t	nbytes = str.length();
	send(clientFd, tosend, nbytes, 0);
}