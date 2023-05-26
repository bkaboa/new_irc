#pragma once

#include "../include.hpp"

namespace irc
{
	class IrcMessage
	{
		public:
			IrcMessage();
			virtual ~IrcMessage();
		 	
			//parsing
			void						parseMessage();
	
			fd_t						getClientRequest() const;
			std::vector<std::string>	getParams() const;
			int							getCommand() const;

			void						recvMessage(const std::string &message);
	
		private:
			fd_t						_ClientRequest;
			std::vector<std::string>	_params;
			int							_Command;
			std::string					_Message;
			bool						_MessageCompleted;
	};
}
