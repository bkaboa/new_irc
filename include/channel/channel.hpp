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
		Channel();
		~Channel();
		const std::string	&getName() const;

	protected:
		void	addMember(irc::Client newMember);

	private:
		bool	checkBan(fd_t clientFd);
		bool	checkOption(int);

		std::string		_Name;
		std::string 	_Topic;
		int				_Option;
		int				_NbUsers;
		mapClient		_Members;
		mapClient		_AdminMembers;
		mapClient		_Operators;// what is _Operators
		vectorFdClient	_FdClientBanned;
	};
}
