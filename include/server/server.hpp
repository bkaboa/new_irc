#pragma once

#include "../include.hpp"
#include "../define.hpp"
#include "../typedef.hpp"
#include "../error.hpp"

namespace irc
{
	class Server
	{
		public:
			Server(std::string portStr, std::string pass);
			Server();
			~Server();
			virtual void	parseMessage(std::string message, fd_t fd);
			virtual	void	sndMessage(std::string message, fd_t fd);

			void					ConnectServer();
			const std::string		&getPass() const;
			mapClientIter			getClient(const fd_t fd) const;
	
		private:
			void	socketInit();
			void	setSocket();
			void	checkEvents();
			void	acceptConnection();
			void	disconnectClient();

			std::string			_Password;
			fd_t				_Port;
			struct sockaddr_in	_SockAddr;
			socket_t			_Sock;
			pollvector			_PollVector;
			mapClient			_ClientMap;
	
	};
}

