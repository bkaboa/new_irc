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
		void channelMsg(fd_t sender, std::string message);
		bool isInChannel(fd_t clientFd);
		void removeMember(fd_t clientFd);
		std::string getName(void);
		bool checkPass(std::string pass);
		void	addMember(irc::Client *newMember, bool admin);
		std::string	getPass(void);
		const std::string getTopic();
		void	setTopic(std::string topic);
		void	joinNameReply(fd_t sender, std::string sendername);
		int		getNumClients(void);
		bool	isAdmin(fd_t client);
		void	kickMember(fd_t fd);
		void	setUserLimit(int limit);
		int		getUserLimit(void);
		void	setOptions(u_int8_t mode);
		u_int8_t getOptions();

	protected : 
		void setAdmin(fd_t fd);

	private:
		bool	checkBan(fd_t clientFd);
		bool	checkOption(int);

		std::string				_Password;
		std::string				_Name;
		std::string 			_Topic;
		int						_ChannelOptions;
		int						_userLimit;
		mapClient				_Members;
		vectorFdClient			_FdAdmin;
		vectorFdClient			_FdClientBanned;
		optionClientInChannel	_ClientOption;
	};
}
