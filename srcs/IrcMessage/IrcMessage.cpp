// #include "../../include/server/server.hpp"
// #include <sys/poll.h>
// #include <sys/socket.h>
// #include "../../include/IrcMessage/IrcMessage.hpp"

// using namespace irc;


// IrcMessage::IrcMessage(std::string message)
// {
// 	this->parseMessage(message);
// }

// IrcMessage::~IrcMessage()
// {

// }

// void IrcMessage::setNickname(std::string str)
// {
// 	this->_nickname = str;
// }

// void IrcMessage::setUsername(std::string str)
// {
// 	this->_username = str;
// }

// void IrcMessage::setHostname(std::string str)
// {
// 	this->_hostname = str;
// }

// void IrcMessage::setCommand(std::string str)
// {
// 	this->_command = str;
// }

// void IrcMessage::setMessage(std::string str)
// {
// 	this->_message = str;
// }

// const std::string IrcMessage::getNickname(void)
// {
// 	return (this->_nickname);
// }

// const std::string IrcMessage::getUsername(void)
// {
// 	return (this->_username);
// }

// const std::string IrcMessage::getHostname(void)
// {
// 	return (this->_hostname);
// }

// const std::string IrcMessage::getCommand(void)
// {
// 	return (this->_command);
// }

// const std::string IrcMessage::getMessage(void)
// {
// 	return (this->_message);
// }

// int main(int ac, char **av)
// {
// 	std::string fullmsg;
// 	av = &av[1];
// 	for (int i = 0; av[i]; i++)
// 	{
// 		fullmsg.append(av[i]);
// 		if (av[i + 1])
// 			fullmsg.append(" ");
// 	}
// 	std::cout << fullmsg << std::endl;
// 	IrcMessage msg(fullmsg, 1);
// }