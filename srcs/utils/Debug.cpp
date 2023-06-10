#include "../../include/include.hpp"

void binParamDisplay(int binparams)
{
	std::cout << NC << "Binparams of command :" << std::endl;
	if (binparams & NONE)
		std::cout << NC << "-NONE" << std::endl;
	if (binparams & CHAN)
		std::cout << NC << "-CHAN" << std::endl;
	if (binparams & NICK)
		std::cout << NC << "-NICK" << std::endl;
	if (binparams & PASS)
		std::cout << NC << "-PASS" << std::endl;
	if (binparams & MESS)
		std::cout << NC << "-MESS" << std::endl;
	if (binparams & USER)
		std::cout << NC << "-USER" << std::endl;
	if (binparams & CAPC)
		std::cout << NC << "-CAPC" << std::endl;
	if (binparams & TARG)
		std::cout << NC << "-TARG" << std::endl;
	if (binparams & MODE)
		std::cout << NC << "-MODE" << std::endl;
}