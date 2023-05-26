#pragma once

#include "../include.hpp"

namespace irc
{
	class Server
	{
		public:
			Server(std::string portStr, std::string pass);
			~Server();

			void					ConnectServer();
			const std::string		&getPass() const;

		protected:
			void			channelNew(Channel &channelNew);
			void			disconnectClient(pollvectorIter &it);
			mapClientIter	getClient(const fd_t fd) const;
	
		private:
			void	socketInit();
			void	setSocket();
			void	checkEvents();
			void	acceptConnection();
			void	clientNew(fd_t clientFd);
			void	processMessage(fd_t sender, char *message);

			std::string			_Password;
			fd_t				_Port;
			struct sockaddr_in	_SockAddr;
			socket_t			_Sock;
			pollvector			_PollVector;
			mapClient			_ClientMap;
			mapChannel			_ChannelMap;
	};
}
