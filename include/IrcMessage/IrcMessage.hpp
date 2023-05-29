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
			struct commandData_t		parseMessage();
	
			fd_t						getClientRequest() const;
			std::vector<std::string>	getParams() const;
			int							getCommand() const;
			std::string					getMessage() const {return (_Message);}

			void						recvMessage(const std::string &message);
	
		private:
			int							checkCommand(std::string &sentence, int *command);
			void						stringSlice(size_t nPos, std::string &original, std::string &sliced);
			void						takeChannels(struct commandData_t *command, std::string &sliceMessage) const;
			void						takeNickname(struct commandData_t *command, std::string &sliceMessage) const;
			void						takePassword(struct commandData_t *command, std::string &sliceMessage) const;
			void						takeMessage(struct commandData_t *command, std::string &sliceMessage) const;
			void						takeUser(struct commandData_t *command, std::string &sliceMessage) const;

			fd_t						_ClientRequest;
			std::vector<std::string>	_params;
			std::string					_Message;

	};
}
