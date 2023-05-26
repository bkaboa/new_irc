#pragma once

#include "../server/server.hpp"

namespace irc
{
class Client : public IrcMessage
{
	public:
		Client(fd_t fd);
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

	private:
		fd_t			_Fd;
		std::string		_Nick;
		std::string 	_Name;
		bool			_IsConnect;
};
}
