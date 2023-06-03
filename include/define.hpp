#pragma once

#include "include.hpp"

#define INETADDR_ANY	"0.0.0.0"

#define RUNTIME			1

#define ACCEPT_CLIENT	1

#define POLL_TIMEOUT	100

#define MESSAGE_LIMIT	511

#define MAX_CHANNELS	10

//***************************		COLORS
#define RED			"\033[0;31m"
#define GREEN		"\033[1;32m"
#define YELLOW		"\033[1;33m"
#define BLUE		"\033[1;34m"
#define NC			"\033[0m"

//***************************		CHANNEL_MODE
enum channelMode:u_int8_t {
	i = 1,	//Set/remove Invite-only channel
	t = 2,	//Set/remove the restrictions of the TOPIC command to channel operators
	k = 4,	//Set/remove the channel key (password)
	o = 8,	//Give/take channel operator privilege
	l = 16	//Set/remove the user limit to channel
};

//***************************		PARSING_TYPE
enum parsingType:u_int8_t {
	NONE = 0,
	CHAN = 1,
	NICK = 2,
	PASS = 4,
	MESS = 8,
	USER = 16,
	CAPC = 32,
	TARG = 64
};

//***************************		COMMAND
#define BAN_MACRO(command)        (command) == "BAN" ? (NICK + MESS) : 0
#define INVITE_MACRO(command)     (command) == "INVITE" ? (CHAN + NICK + PASS + MESS) : 0
#define JOIN_MACRO(command)       (command) == "JOIN" ? (CHAN + NICK + PASS) : 0
#define KICK_MACRO(command)       (command) == "KICK" ? (CHAN + NICK + MESS) : 0
#define LIST_MACRO(command)       (command) == "LIST" ? (CHAN) : 0
#define NICK_MACRO(command)       (command) == "NICK" ? (NICK) : 0
#define PART_MACRO(command)       (command) == "PART" ? (CHAN + MESS) : 0
#define PASS_MACRO(command)       (command) == "PASS" ? (PASS) : 0
#define PRIVMSG_MACRO(command)    (command) == "PRIVMSG" ? (TARG + MESS) : 0
#define QUIT_MACRO(command)       (command) == "QUIT" ? (MESS) : 0
#define TOPIC_MACRO(command)      (command) == "TOPIC" ? (CHAN + MESS) : 0
#define USER_MACRO(command)       (command) == "USER" ? (USER) : 0
#define CAP_MACRO(command)        (command) == "CAP" ? (CAPC) : 0

//***************************		SERVER_ERR
#define ERR_INPUTTOOLONG(client) std::string(client) + " :Input line was too long\r\n"
#define ERR_UNKNOWNCOMMAND(client, command) std::string(client) + std::string(command) + " :Unknown command\r\n"
#define ERR_NOSUCHNICK(client, nick) std::string(client) + " " + std::string(nick) + " :No such nick/channel\r\n"
#define ERR_NOSUCHSERVER(client, server) std::string(client) + " " + std::string(server) + " :No such server\r\n"
#define ERR_NOSUCHCHANNEL(client, chan) std::string(client) + " " + std::string(chan) + " :No such channel\r\n"
#define ERR_CANNOTSENDTOCHAN(client, chan) std::string(client) + " " + std::string(chan) + " :Cannot send to channel\r\n"
#define ERR_TOOMANYCHANNELS(client, chan) std::string(client) + " " + std::string(chan) + " :You have joined too many channels\r\n"
#define ERR_WASNOSUCHNICK(client) std::string(client) + " :There was no such nickname\r\n"
#define ERR_NORECIPIENT(client, command) std::string(client) + " :No recipient given " + std::string(command) + "\r\n"
#define ERR_NOTEXTTOSEND(client) std::string(client) + " :No text to send\r\n"
#define ERR_NONICKNAMEGIVEN(client) std::string(client) + " :No nickname given\r\n"
#define ERR_ERRONEUSNICKNAME(client, nick) std::string(client) + " " + std::string(nick) + " :Erroneus nickname\r\n"
#define ERR_NICKNAMEINUSE(client, nick) std::string(client) + " " + std::string(nick) + " :Nickname is already in use\r\n"
#define ERR_USERNOTINCHANNEL(client, nick, chan) std::string(client) + " " + std::string(nick) + " " + std::string(chan) + " :They aren't on that channel\r\n"
#define ERR_NOTONCHANNEL(client, chan) std::string(client) + " " + std::string(chan) + " :You're not on that channel\r\n"
#define ERR_USERONCHANNEL(client, nick, chan) std::string(client) + " " + std::string(nick) + " " + std::string(chan) + " :is already on channel\r\n"
#define ERR_NOTREGISTERED(client) std::string(client) + " :You have not registered\r\n"
#define ERR_NEEDMOREPARAMS(client, command) std::string(client) + " " + std::string(command) + " :Not enough parameters\r\n"
#define ERR_ALREADYREGISTERED(client) std::string(client) + " :You may not reregister\r\n"
#define ERR_PASSWDMISMATCH(client) std::string(client) + " :Password incorrect\r\n"
#define ERR_YOUREBANNEDCREEP(client) std::string(client) + " :You are banned from this server\r\n"
#define ERR_CHANNELISFULL(client, chan) std::string(client) + " " + std::string(chan) + " :Cannot join channel, it is full\r\n"
#define ERR_UNKNOWNMODE(client, mode) std::string(client) + " " + std::string(mode) + " :is unknown mode char to me\r\n"
#define ERR_INVITEONLYCHAN(client, chan) std::string(client) + " " + std::string(chan) + " :Cannot join channel, invite only\r\n"
#define ERR_BANNEDFROMCHAN(client, chan) std::string(client) + " " + std::string(chan) + " :Cannot join channel, you are banned\r\n"
#define ERR_BADCHANNELKEY(client, chan) std::string(client) + " " + std::string(chan) + " :Cannot join channel, you need the right key\r\n"
#define ERR_NOPRIVILEGES(client) std::string(client) + " :Permission Denied- You're not an IRC operator\r\n"
#define ERR_CHANOPRIVSNEEDED(client, chan) std::string(client) + " " + std::string(chan) + " :Your're not channel operator\r\n"
#define ERR_UMODEUNKNOWNFLAG(client) std::string(client) + " :Unknown MODE flag\r\n"
#define ERR_USERSDONTMATCH(client) std::string(client) + " :Can't change mode for other users\r\n"

//*****************SERVER_RPL
#define RPL_WELCOME(client, networkname, nick, user, host) std::string(client) + " :Welcome to the " + std::string (networkname) + " Network, " + std::string(nick) + "[!" + std::string(user) + "@" + std::string(host) + "]\r\n"
#define RPL_TOPIC(client, chan, topic) std::string(client) + " " + std::string(chan) + " :" + std::string(topic) + "\r\n"
#define RPL_LIST(client, chan, clientcount, topic) std::string(client) + " " + std::string(chan) + " " + int(clientcount) + " :" + std::string(topic) + "\r\n"
#define RPL_NAMREPLY(client, symbol, channel, prefix, nick)
#define RPL_ENDOFNAMES(client, channel) std::string(client) + " " + std::string(channel) + " :End of /NAMES list\r\n"
