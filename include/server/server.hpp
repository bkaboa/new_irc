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
			~Server();
			void	ConnectServer();
	
		private:
			void	socketInit();
			void	setSocket();

			std::string			_Password;
			fd_t				_Port;
			struct sockaddr_in	_SockAddr;
			socket_t			_Sock;
			pollvector			_PollVector;
			mapClient			_ClientMap;
	
	};
}

