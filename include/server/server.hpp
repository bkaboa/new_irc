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

			//Commands
			void Ban(fd_t sender, std::vector<std::string> args);
			void Invite(fd_t sender, std::vector<std::string> args);
			void Join(fd_t sender, std::vector<std::string> args);
			void Kick(fd_t sender, std::vector<std::string> args);
			void List(fd_t sender, std::vector<std::string> args);
			void Nick(fd_t sender, std::vector<std::string> args);
			void Part(fd_t sender, std::vector<std::string> args);
			void Pass(fd_t sender, std::vector<std::string> args);
			void Privmsg(fd_t sender, std::vector<std::string> args);
			void Quit(fd_t sender, std::vector<std::string> args);
			void Topic(fd_t sender, std::vector<std::string> args);
			void User(fd_t sender, std::vector<std::string> args);
	};
}

void sendStr(std::string str);