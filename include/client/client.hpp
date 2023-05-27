#pragma once

#include "../include.hpp"
#include "../IrcMessage/IrcMessage.hpp"

namespace irc
{
	class Client : public IrcMessage
	{
		public:
			Client(fd_t fd);
			Client();
			~Client();
			void				setClient(const std::string &Nick, const std::string &name, bool isConnect);
			const std::string	&getName() const;
			const std::string	&getNick() const;
			bool				isConnect() const;
			void				changeName(const std::string &name);
			void				changeNick(const std::string &nick);
			fd_t				getFd() const;
			bool				getAdmin() const;
			void				setAdmin(bool Admin);
			void				setIsConnect(bool truefalse);
			void				setPassOk(bool truefalse);
			void				setNickOk(bool truefalse);
			bool				getPassOk(void);
			bool				getNickOk(void);
	
		private:
			fd_t			_Fd;
			std::string		_Nick;
			std::string 	_Name;
			bool			_IsConnect;
			bool			_passOk;
			bool			_nickOk;
	};
}
