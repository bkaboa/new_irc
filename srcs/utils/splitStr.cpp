#include "../../include/include.hpp"

std::vector<std::string> strSplit(const std::string &str, char separator)
{
	std::vector<std::string> output;
	size_t prev_pos = 0, pos = 0;

	while ((pos = str.find(separator, pos)) != std::string::npos)
	{
		std::string substring(str.substr(prev_pos, pos - prev_pos));
		output.push_back(substring);
		prev_pos = ++pos;
	}
	output.push_back(str.substr(prev_pos, pos - prev_pos));
	return (output);
}