#include "../../include/include.hpp"

std::vector<std::string> strSplit(const std::string &str, char separator)
{
	std::vector<std::string> output;
	size_t prev_pos = 0, pos = 0;

	while((pos = str.find(separator, pos)) != std::string::npos)
	{
		std::string substring(str.substr(prev_pos, pos - prev_pos));
		output.push_back(substring);
		prev_pos = ++pos;
	}
	output.push_back(str.substr(prev_pos, pos - prev_pos));
	return(output);
}

// int	msgParsing(std::string message)
// {
// 	if (message[0] != '/')
// 		return (-1);
// 	if (message.find(' ', 0) <= 1)
// }

int main(void)
{
	std::string msg1 = "salut je suis un message";
	std::string msg2 = "/join je suis une commande";
	std::vector<std::string> tab = strSplit(msg2, ' ');
	for (int i = 0; i < tab.size(); i++)
		std::cout << tab[i] << std::endl;

}