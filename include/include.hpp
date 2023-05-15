#pragma once

// ************		BASE-INCLUDE
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <map>
#include <signal.h>
#include <utility>
#include <sys/signal.h>

// ************		HANDLING-ERROR
#include <cerrno>

// ************		NETWORK
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>
#include <netinet/in.h>
#include <fcntl.h>

// ************		OUR_INCLUDES
#include "define.hpp"
#include "typedef.hpp"
#include "error.hpp"
#include "client/client.hpp"
