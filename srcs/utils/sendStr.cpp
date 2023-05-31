#include "../../include/include.hpp"

void	sendStr(fd_t clientFd, std::string str)
{
	const char *tosend = str.c_str();
	size_t	nbytes = str.length();
	int bytesSent = send(clientFd, tosend, nbytes, 0);
	if (bytesSent == -1)
	{
		//error
	}
	else
	{
		//success
	}
}