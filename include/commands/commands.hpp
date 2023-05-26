#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "../include.hpp"
#include "../server/server.hpp"

using namespace irc;


//All commands definitions

void Ban(fd_t sender, Server *server, std::vector<std::string> args);
void Invite(fd_t sender, Server *server, std::vector<std::string> args);
void Join(fd_t sender, Server *server, std::vector<std::string> args);
void Kick(fd_t sender, Server *server, std::vector<std::string> args);
void List(fd_t sender, Server *server, std::vector<std::string> args);
void Nick(fd_t sender, Server *server, std::vector<std::string> args);
void Part(fd_t sender, Server *server, std::vector<std::string> args);
void Pass(fd_t sender, Server *server, std::vector<std::string> args);
void Privmsg(fd_t sender, Server *server, std::vector<std::string> args);
void Quit(fd_t sender, Server *server, std::vector<std::string> args);
void Topic(fd_t sender, Server *server, std::vector<std::string> args);
void User(fd_t sender, Server *server, std::vector<std::string> args);

#endif