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
			mapClientIter			getClient(const fd_t fd) const;
	
		private:
			void	socketInit();
			void	setSocket();
			void	checkEvents();
			void	acceptConnection();
			void	disconnectClient();
			void	clientNew(fd_t clientFd);

			std::string			_Password;
			fd_t				_Port;
			struct sockaddr_in	_SockAddr;
			socket_t			_Sock;
			pollvector			_PollVector;
			mapClient			_ClientMap;
	
	};
}

