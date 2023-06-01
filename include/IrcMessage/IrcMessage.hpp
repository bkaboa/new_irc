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
			void						parseMessage(commandList &commandList);
	
			fd_t						getClientRequest() const;
			std::vector<std::string>	getParams() const;
			int							getCommand() const;

			void						recvMessage(std::string message);
	
		private:
			void						checkCommand(std::string &sentence, int *binParams, int *command);
			bool						stringSlice(size_t nPos, std::string &original, std::string &sliced);
			void						takeTarget(struct commandData_t *command, std::string &sliceMessage);
			void						takeMessage(struct commandData_t *command, std::string &sliceMessage);
			void						takeChannel(struct commandData_t *command, std::string &sliceMessage);
			void						takeNick(struct commandData_t *command, std::string &sliceMessage);
			void						takeUser(struct commandData_t *command, std::string &sliceMessage);
			void						takePass(struct commandData_t *command, std::string &sliceMessage);

			fd_t						_ClientRequest;
			std::vector<std::string>	_params;
			std::string					_Message;

	};
}
