#ifndef IRCMESSAGE_HPP
#define IRCMESSAGE_HPP

#include "../include.hpp"
#include "../define.hpp"
#include "../typedef.hpp"
#include "../error.hpp"

class IrcMessage
{
	private:
		std::string _nickname;
		std::string _username;
		std::string _hostname;
		std::string _command;
		std::vector<std::string> _params;
		std::string _message;
		fd_t	_target;

	public:
		IrcMessage(std::string message);
		~IrcMessage();
		
		//parsing
		void parseMessage(std::string message);

		//Setter
		void setNickname(std::string str);
		void setUsername(std::string str);
		void setHostname(std::string str);
		void setCommand(std::string str);
		void setMessage(std::string str);

		//Getter
		const std::string getNickname(void);
		const std::string getUsername(void);
		const std::string getHostname(void);
		const std::string getCommand(void);
		const std::string getMessage(void);
};

#endif