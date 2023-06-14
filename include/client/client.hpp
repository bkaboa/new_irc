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
			bool				isRegistered() const;
			void				changeName(const std::string &name);
			void				changeNick(const std::string &nick);
			fd_t				getFd() const;
			bool				getAdmin() const;
			void				setAdmin(bool Admin);
			void				setIsRegistered(bool truefalse);
			void				setPassOk(bool truefalse);
			bool				getPassOk(void) const;
			void				setNickOk(bool truefalse);
			bool				getNickOk(void) const;
			void				setUserOk(bool truefalse);
			bool				getUserOk(void) const;
	
		private:
			fd_t			_Fd;
			std::string		_Nick;
			std::string 	_Name;
			bool			_IsRegistered;
			bool			_passOk;
			bool			_nickOk;
			bool			_userOk;
	};
}
