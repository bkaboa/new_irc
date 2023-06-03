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
		bool isInChannel(fd_t clientFd);
		void removeMember(fd_t clientFd);
		std::string getName(void);
		bool checkPass(std::string pass);
		void	addMember(irc::Client *newMember, bool admin);
		std::string	getPass(void);

	protected:
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
