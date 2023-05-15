#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "../include.hpp"
#include "../define.hpp"
#include "../typedef.hpp"
#include "../error.hpp"
#include "../client/client.hpp"


namespace irc
{
	class Channel
	{
	private:
		std::string _name;
		std::string _topic;
		int	_nbUsers;
		std::map<int, Client> _members; //map of clients (or users), with key fd and value Client
		std::map<int, Client> _operators;
		std::vector<std::string> _banned; //list of banned users

	public:
		Channel();
		~Channel();
		void addMember(irc::Client newMember);
		bool checkBan(std::string name);
	};

}


#endif