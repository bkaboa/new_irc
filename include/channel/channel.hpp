#pragma once

#include "../include.hpp"
#include "../define.hpp"
#include "../typedef.hpp"
#include "../error.hpp"
#include "../client/client.hpp"

namespace irc
{
	class Channel
	{
	public:
		Channel(Client* creator);
		~Channel();
		const std::string	&getName() const;

	protected:
		void	addMember(irc::Client *newMember, bool admin);
		void	setAdmin(fd_t fd);
		void	kickMember(fd_t fd);

	private:
		bool	checkBan(fd_t clientFd);
		bool	checkOption(int);

		std::string			_Name;
		std::string 		_Topic;
		int					_Options;
		mapClient			_Members;
		vectorFdClient		_FdAdmin;
		vectorFdClient		_FdClientBanned;
	};
}
