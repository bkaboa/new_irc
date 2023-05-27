#pragma once

#include "include.hpp"

#define INETADDR_ANY	"0.0.0.0"

#define RUNTIME			1

#define ACCEPT_CLIENT	1

#define POLL_TIMEOUT	100

#define MESSAGE_LIMIT	511

//***************************		COLORS
#define RED			"\033[0;31m"
#define GREEN		"\033[1;32m"
#define YELLOW		"\033[1;33m"
#define BLUE		"\033[1;34m"
#define NC			"\033[0m"

//***************************		CHANNEL_OPTION
#define ONLY_INVIT	1


//***************************		COMMAND
#define COMMAND_NAME {std::string("JOIN"), std::string("PASS")}


//***************************		SERVER_REPLY
#define ERR_INPUTTOOLONG (client) std::string(client) + " :Input line was too long"

#define ERR_UNKNOWNCOMMAND (client)(command) std::string(client) + std::string(command) + " :Unknown command"
