#pragma once

#include "../include.hpp"

class IrcMessage
{
	public:
		IrcMessage();
		~IrcMessage();
		
		//parsing
		void parseMessage(std::string message);

		fd_t						getClientRequest() const;
		std::vector<std::string>	getParams() const;
		int							getCommand() const;

	private:
		fd_t						_ClientRequest;
		std::vector<std::string>	_params;
		int							_Command;
		std::string					_message;
};
