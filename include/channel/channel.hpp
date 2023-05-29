#pragma once

#include "../include.hpp"

namespace irc
{
	class Channel
	{
	public:
		Channel(Client* creator, const std::string &name, const std::string &pass);
		~Channel();
		const std::string	&getName() const;
		void channelMsg(std::string message);

	protected:
		void	addMember(irc::Client *newMember, bool admin);
		void	setAdmin(fd_t fd);
		void	kickMember(fd_t fd);

	private:
		bool	checkBan(fd_t clientFd);
		bool	checkOption(int);

		std::string				_Password;
		std::string				_Name;
		std::string 			_Topic;
		int						_ChannelOptions;
		mapClient				_Members;
		vectorFdClient			_FdAdmin;
		vectorFdClient			_FdClientBanned;
		optionClientInChannel	_ClientOption;
	};
}
