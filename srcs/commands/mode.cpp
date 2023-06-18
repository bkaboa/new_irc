#include "../../include/include.hpp"
#include "../../include/IrcMessage/IrcMessage.hpp"
#include "../../include/server/server.hpp"
#include "../../include/channel/channel.hpp"
#include "../../include/client/client.hpp"

using namespace irc;

//  i: toggle Invite-only channel
static void	channelmode_i(int sign, Channel *channel)
{
	if (sign && !(channel->getOptions() & i))
		channel->setOptions(i, sign);
	else if (!sign && (channel->getOptions() & i))
	{
		channel->clearInvite();
		channel->setOptions(i, sign);
	}
}

//  t: toggle the restrictions of the TOPIC command to channel operators
static void channelmode_t(int sign, Channel *channel)
{
	if (sign && !(channel->getOptions() & t))
		channel->setOptions(t, sign);
	else if (!sign && (channel->getOptions() & t))
		channel->setOptions(t, sign);
}

//  k: Set/remove the channel key (password)
static void channelmode_k(fd_t sender, int sign, Channel *channel, std::string pass)
{
	if (sign && !(channel->getOptions() & k))
	{
		if (pass.empty())
		{
			sendStr(sender, "Error : In order to Mode a key to the channel, you need to enter a password !\r\n");
			return;
		}
		channel->setOptions(k, sign);
		channel->setPassword(pass);
	}
	else if (!sign && (channel->getOptions() & k))
	{
		channel->setOptions(k, sign);
		channel->setPassword("");
	}
}

//  l: Set/remove the user limit to channel
static void channelmode_l(int sign, Channel *channel, int limit)
{
	if (sign && !(channel->getOptions() & l))
	{
		channel->setOptions(l, sign);
		if (limit > 1)
			channel->setUserLimit(limit);
	}
	else if (!sign && (channel->getOptions() & l))
		channel->setOptions(l, sign);
}

static void modeReply(std::string reply, Channel *channel)
{
	if (!(reply.empty()))
	{
		reply += "\r\n";
		channel->channelMsg(-1, reply);
		reply.clear();
	}
}

void Server::Mode(fd_t sender, const commandData_t &args)
{
	if (!(_ClientMap[sender]->isRegistered()))
	{
		sendStr(sender, ERR_NOTREGISTERED(_ClientMap[sender]->getNick()));
		return;
	}
	if (args.binParams == NONE || !(args.binParams & CHAN))
	{
		sendStr(sender, ERR_NEEDMOREPARAMS(_ClientMap[sender]->getNick(), "MODE"));
		return;
	}
	std::string target = args.params[0];
	if (target[0] == '#' || target[0] == '&')
	{
		if (_ChannelMap.find(target) == _ChannelMap.end())
		{
			sendStr(sender, ERR_NOSUCHCHANNEL(_ClientMap[sender]->getNick(), target));
			return;
		}
		if (!(_ChannelMap.find(target)->second->isInChannel(sender)))
		{
			sendStr(sender, ERR_NOTONCHANNEL(_ClientMap[sender]->getNick(), target));
			return;
		}
		//can exec
		else
		{
			Channel *channel = _ChannelMap.find(target)->second;
			//no mode change, display of channel modes
			if (!(args.binParams & MODE))
			{
				std::string replymodestring = "";
				std::string replyuserlimit = "";
				if (channel->getOptions() != noOptions)
					replymodestring += "+";
				if (channel->getOptions() & i)
					replymodestring += "i";
				if (channel->getOptions() & t)
					replymodestring += "t";
				if (channel->getOptions() & k)
					replymodestring += "k";
				if (channel->getOptions() & l)
				{
					replymodestring += "l";
					replyuserlimit = channel->getUserLimit();
				}
				sendStr(sender, RPL_CHANNELMODEIS(_ClientMap[sender]->getNick(), target, replymodestring, replyuserlimit));
				return;
			}
			//mode changes
			else if (args.binParams & MODE)
			{
				if (!channel->isAdmin(sender))
				{
					sendStr(sender, ERR_CHANOPRIVSNEEDED(_ClientMap[sender]->getNick(), channel->getName()));
					return;
				}
				std::string mreply;
				int sign = -1;
				std::string modestring = args.params[1];
				std::string modeparam = "";
				if (args.params.size() > 2)
					modeparam = args.params[2];
				for (int index = 1; index < static_cast<int>(modestring.size()); index++)
				{
					mreply = std::string(":") + SERVER_NAME + " MODE " + target;
					if (modestring[0] == '+')
					{
						mreply += " +";
						sign = 1;
					}
					if (modestring[0] == '-')
					{
						mreply += " -";
						sign = 0;
					}
					if (modestring[index] == 'i')
					{
						mreply += std::string("i");
						modeReply(mreply, channel);
						channelmode_i(sign, channel);
					}
					else if (modestring[index] == 't')
					{
						mreply += std::string("t");
						modeReply(mreply, channel);
						channelmode_t(sign, channel);
					}
					else if (modestring[index] == 'k')
					{
						mreply += std::string("k");
						modeReply(mreply, channel);
						channelmode_k(sender, sign, channel, modeparam);
					}
					else if (modestring[index] == 'l')
					{
						mreply += std::string("l") + " " + modeparam;
						modeReply(mreply, channel);
						channelmode_l(sign, channel, ft_stoi(modeparam));
					}
					//mode o : give / take operator privileges
					else if (modestring[index] == 'o')
					{
						mreply += std::string("o") + " " + modeparam;
						fd_t targetfd = getClientFd(modeparam);
						if (targetfd == -1)
						{
							mreply.clear();
							sendStr(sender, ERR_NOSUCHNICK(_ClientMap[sender]->getNick(), modeparam));
						}
						else if (sender == targetfd)
							mreply.clear();
						else if (!channel->isInChannel(targetfd))
						{
							mreply.clear();
							sendStr(sender, ERR_USERNOTINCHANNEL(_ClientMap[sender]->getNick(), modeparam, target));
						}
						else
						{
							if (sign && !channel->isAdmin(targetfd))
								channel->setAdmin(targetfd, true);
							else if (!sign && channel->isAdmin(targetfd))
								channel->setAdmin(targetfd, false);
							modeReply(mreply, channel);
						}
					}
					else
					{
						sendStr(sender, ERR_UMODEUNKNOWNFLAG(_ClientMap[sender]->getNick()));
						mreply.clear();
					}
				}
				return;
			}
		}
	}
}
