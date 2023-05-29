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
			void	execCommand(commandData_t &cmd);

			std::string			_Password;
			fd_t				_Port;
			struct sockaddr_in	_SockAddr;
			socket_t			_Sock;
			pollvector			_PollVector;
			mapClient			_ClientMap;
			mapChannel			_ChannelMap;

			// Commands
			void Ban(fd_t sender, std::list<struct paramsData_t>);
			void Invite(fd_t sender, std::list<struct paramsData_t>);
			void Join(fd_t sender, std::list<struct paramsData_t>);
			void Kick(fd_t sender, std::list<struct paramsData_t>);
			void List(fd_t sender, std::list<struct paramsData_t>);
			void Nick(fd_t sender, std::list<struct paramsData_t>);
			void Part(fd_t sender, std::list<struct paramsData_t>);
			void Pass(fd_t sender, std::list<struct paramsData_t>);
			void Privmsg(fd_t sender, std::list<struct paramsData_t>);
			void Quit(fd_t sender, std::list<struct paramsData_t>);
			void Topic(fd_t sender, std::list<struct paramsData_t>);
			void User(fd_t sender, std::list<struct paramsData_t>);
	};
}

void sendStr(std::string str);
