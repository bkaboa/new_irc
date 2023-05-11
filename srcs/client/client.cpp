#include "../../include/client/client.hpp"

using namespace irc;

Client::Client(fd_t fd):_Fd(fd) {}

Client::~Client() {}

// void	Client::setClient(const std::string &Nick, const std::string &name, bool isConnect)
// {

// 	if (pass == getPass())
// 		
// }
