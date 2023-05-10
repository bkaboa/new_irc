#pragma once

#include "include.hpp"

class	Client;
typedef	u_int32_t				fd_t;
typedef u_int32_t				socket_t;
typedef std::vector<pollfd>		pollvector;
typedef std::map<fd_t, Client*>	mapClient;
