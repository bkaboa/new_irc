#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"
#include "../../include/channel/channel.hpp"

using namespace irc;

static void	channelmode_i(fd_t sender, int sign, Channel *channel)
{

}

static void channelmode_t(fd_t sender, int sign, Channel *channel)
{
}

static void channelmode_k(fd_t sender, int sign, Channel *channel, std::string pass)
{
}

static void channelmode_l(fd_t sender, int sign, Channel *channel, int limit)
{
}

static void channelmode_o(fd_t sender, int sign, Channel *channel, std::string usertarg)
{
}

void Server::Mode(fd_t sender, const commandData_t &args)
{
	// user mode :
	// mode for channel only :
	//  i: toggle Invite-only channel
	//  t: toggle the restrictions of the TOPIC command to channel operators
	//  k: Set/remove the channel key (password)
	//  l: Set/remove the user limit to channel
	//  o: Give/take channel operator privilege
	if (!(_ClientMap[sender]->isRegistered()))
	{
		sendStr(sender, ERR_NOTREGISTERED(_ClientMap[sender]->getNick()));
		return;
	}
	if (args.binParams == NONE || !(args.binParams & TARG))
	{
		sendStr(sender, ERR_NEEDMOREPARAMS(_ClientMap[sender]->getNick(), "MODE"));
		return;
	}
	std::string target = args.params[0];
	//target is a channel
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
		if (!(_ChannelMap.find(target)->second->isAdmin(sender)))
		{
			sendStr(sender, ERR_CHANOPRIVSNEEDED(_ClientMap[sender]->getNick(), target));
			return;
		}
		//can exec
		else
		{
			Channel *chan = _ChannelMap.find(target)->second;
			//no mode, default mode display of channel
			if (!(args.binParams & MODE))
			{
				std::string replymodestring = "";
				std::string replyuserlimit = "";
				if (chan->getOptions() & l)
				{
					
					replyuserlimit = std::to_string(chan->getUserLimit());
				}
				sendStr(sender, RPL_CHANNELMODEIS(_ClientMap[sender]->getNick(), target, replymodestring, replyuserlimit));
				return;
			}
			//check modes
			else
			{
				int sign = 0;
				std::string modestring = args.params[1];
				std::string modeparam = "";
				if (!args.params[2].empty())
					modeparam = args.params[2];
				if (modestring[0] == '+')
					sign = 1;
				if (modestring[0] == '-')
					sign = -1;
				for (int i = 1; i < modestring.size(); i++)
				{
					if (modestring[i] == 'i')
						channelmode_i(sender, sign, chan);
					else if (modestring[i] == 't')
						channelmode_t(sender, sign, chan);
					else if (modestring[i] == 'k')
						channelmode_k(sender, sign, chan, modeparam);
					else if (modestring[i] == 'l')
						channelmode_l(sender, sign, chan, ft_stoi(modeparam));
					else if (modestring[i] == 'o')
						channelmode_o(sender, sign, chan, modeparam);
				}
			}
		}
	}
}