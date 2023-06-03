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
			void			channelNew(Client *creator, std::string name, std::string pass);
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
			void Ban(fd_t sender, const commandData_t &args);
			void Invite(fd_t sender, const commandData_t &args);
			void Join(fd_t sender, const commandData_t &args);
			void Kick(fd_t sender, const commandData_t &args);
			void List(fd_t sender, const commandData_t &args);
			void Nick(fd_t sender, const commandData_t &args);
			void Part(fd_t sender, const commandData_t &args);
			void Pass(fd_t sender, const commandData_t &args);
			void Privmsg(fd_t sender, const commandData_t &args);
			void Quit(fd_t sender, const commandData_t &args);
			void Topic(fd_t sender, const commandData_t &args);
			void User(fd_t sender, const commandData_t &args);
	};
}

void sendStr(fd_t dest, std::string str);
std::vector<std::string> strSplit(const std::string &str, char separator);