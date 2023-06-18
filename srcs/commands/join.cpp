#include "../../include/server/server.hpp"
#include "../../include/client/client.hpp"
#include "../../include/channel/channel.hpp"

using namespace irc;

void Server::Join(fd_t sender, const commandData_t &args)
{
	if (!(_ClientMap[sender]->isRegistered()))
	{
		sendStr(sender, "You are not registered on this server...\r\n");
		return;
	}
	if (args.binParams == NONE || !(args.binParams & CHAN))
		sendStr(sender, ERR_NEEDMOREPARAMS(_ClientMap[sender]->getNick(), "JOIN"));
	else if (_ChannelMap.size() < MAX_CHANNELS)
	{
		std::vector<std::string> channelsToJoin = strSplit(args.params[0], ',');
		std::vector<std::string>::iterator iter = channelsToJoin.begin();
		//JOIN without pass
		if (!(args.binParams & PASS))
		{
			for (; iter != channelsToJoin.end(); ++iter)
			{
				//channel does not exist
				if (_ChannelMap.find(*iter) == _ChannelMap.end())
				{
					std::string newChanName = *iter;
					if (newChanName[0] == '#' || newChanName[0] == '&')
					{
						//creating channel without pass
						if (_ChannelMap.size() < MAX_CHANNELS)
						{
							std::string reply = ":" + _ClientMap[sender]->getNick() + "!" + _ClientMap[sender]->getName() + " JOIN " + newChanName + "\r\n";
							channelNew(_ClientMap[sender], newChanName, "");
							_ChannelMap[newChanName]->channelMsg(-1, reply);
							_ChannelMap[newChanName]->joinNameReply(sender, _ClientMap[sender]->getName());
						}
						else
							sendStr(sender, ERR_TOOMANYCHANNELS(_ClientMap[sender]->getNick(), newChanName));
					}
					else 
						sendStr(sender, "To create a Channel, you need to add the prefix # or &\r\n");
				}
				//channel does exist
				else
				{
					Channel *chan = _ChannelMap[*iter];
					//user is already on channel
					if (chan->isInChannel(sender))
						sendStr(sender, ERR_USERONCHANNEL(_ClientMap[sender]->getNick(), _ClientMap[sender]->getNick(), chan->getName()));
					//if user is not in channel
					else if (!(chan->isInChannel(sender)))
					{
						//channel has password
						if (chan->getOptions() & k)
							sendStr(sender, ERR_BADCHANNELKEY(_ClientMap[sender]->getNick(), chan->getName()));
						//channel does not need password to be joined
						else
						{
							//channel has invite only mode
							if (chan->getOptions() & i)
							{
								if (chan->isInvited(sender) || chan->isAdmin(sender))
								{
									chan->removeInvite(sender);
									std::string reply = ":" + _ClientMap[sender]->getNick() + "!" + _ClientMap[sender]->getName() + " JOIN " + chan->getName() + "\r\n";
									chan->addMember(_ClientMap[sender], 0);
									chan->channelMsg(-1, reply);
									chan->joinNameReply(sender, _ClientMap[sender]->getNick());
									std::cout << YELLOW << sender << std::endl;
								}
								else if (!chan->isInvited(sender))
									sendStr(sender, ERR_INVITEONLYCHAN(_ClientMap[sender]->getNick(), chan->getName()));
							}
							//no invite only, just join
							else
							{
								chan->addMember(_ClientMap[sender], 0);
								std::string reply = ":" + _ClientMap[sender]->getNick() + "!" + _ClientMap[sender]->getName() + " JOIN " + chan->getName() + "\r\n";
								chan->channelMsg(-1, reply);
								chan->joinNameReply(sender, _ClientMap[sender]->getName());
							}
						}
					}
				}
			}
		}
		else if (args.binParams & PASS)
		{
			std::vector<std::string> passwords = strSplit(args.params[1], ',');
			std::vector<std::string>::iterator passiter = passwords.begin();
			for (; iter != channelsToJoin.end(); ++iter, ++passiter)
			{
				// channel does not exist
				if (_ChannelMap.find(*iter) == _ChannelMap.end())
				{
					std::string newChanName = *iter;
					if (newChanName[0] == '#' || newChanName[0] == '&')
					{
						std::string reply = ":" + _ClientMap[sender]->getNick() + "!" + _ClientMap[sender]->getName() + " JOIN " + newChanName + "\r\n";
						// creating channel with password
						if (passiter != passwords.end() && _ChannelMap.size() < MAX_CHANNELS)
						{
							channelNew(_ClientMap[sender], newChanName, *passiter);
							_ChannelMap[newChanName]->channelMsg(-1, reply);
							_ChannelMap[newChanName]->joinNameReply(sender, _ClientMap[sender]->getName());
						}
						// creating channel without pass
						else if (_ChannelMap.size() < MAX_CHANNELS)
						{
							channelNew(_ClientMap[sender], newChanName, "");
							_ChannelMap[newChanName]->channelMsg(-1, reply);
							_ChannelMap[newChanName]->joinNameReply(sender, _ClientMap[sender]->getName());
						}
						else
							sendStr(sender, ERR_TOOMANYCHANNELS(_ClientMap[sender]->getNick(), newChanName));
					}
					else
						sendStr(sender, "To create a Channel, you need to add the prefix # or &\r\n");
				}
				// channel does exist
				else
				{
					Channel *chan = _ChannelMap[*iter];
					if (chan->isInChannel(sender))
						sendStr(sender, ERR_USERONCHANNEL(_ClientMap[sender]->getNick(), _ClientMap[sender]->getNick(), chan->getName()));
					// if user is not in channel
					else if (!(chan->isInChannel(sender)))
					{
						// channel has password
						if (chan->getOptions() & k)
						{
							if (chan->getOptions() & i)
							{
								if (chan->checkPass(*passiter))
								{
									if (chan->isInvited(sender))
									{
										if ((chan->getOptions() & l) && (chan->getMembersSize() > chan->getUserLimit()))
											sendStr(sender, ERR_CHANNELISFULL(_ClientMap[sender]->getNick(), chan->getName()));
										else
										{
											chan->addMember(_ClientMap[sender], 0);
											std::string reply = ":" + _ClientMap[sender]->getNick() + "!" + _ClientMap[sender]->getName() + " JOIN " + chan->getName() + "\r\n";
											chan->channelMsg(-1, reply);
											chan->joinNameReply(sender, _ClientMap[sender]->getNick());
											chan->removeInvite(sender);
										}
									}
									else
										sendStr(sender, ERR_INVITEONLYCHAN(_ClientMap[sender]->getNick(), chan->getName()));
								}
								else
									sendStr(sender, ERR_BADCHANNELKEY(_ClientMap[sender]->getNick(), chan->getName()));
							}
							else
							{
								if (chan->checkPass(*passiter))
								{
									if ((chan->getOptions() & l) && (chan->getMembersSize() > chan->getUserLimit()))
										sendStr(sender, ERR_CHANNELISFULL(_ClientMap[sender]->getNick(), chan->getName()));
									else
									{
										chan->addMember(_ClientMap[sender], 0);
										std::string reply = ":" + _ClientMap[sender]->getNick() + "!" + _ClientMap[sender]->getName() + " JOIN " + chan->getName() + "\r\n";
										chan->channelMsg(-1, reply);
										chan->joinNameReply(sender, _ClientMap[sender]->getNick());
										chan->removeInvite(sender);
									}
								}
								else
									sendStr(sender, ERR_BADCHANNELKEY(_ClientMap[sender]->getNick(), chan->getName()));
							}
						}
						// channel does not need password to be joined
						else
						{
							if ((chan->getOptions() & l) && (chan->getMembersSize() > chan->getUserLimit()))
								sendStr(sender, ERR_CHANNELISFULL(_ClientMap[sender]->getNick(), chan->getName()));
							else
							{
								chan->addMember(_ClientMap[sender], 0);
								std::string reply = ":" + _ClientMap[sender]->getNick() + "!" + _ClientMap[sender]->getName() + " JOIN " + chan->getName() + "\r\n";
								chan->channelMsg(-1, reply);
								chan->joinNameReply(sender, _ClientMap[sender]->getNick());
								chan->removeInvite(sender);
							}
						}
					}
				}
			}
		}
	}
}