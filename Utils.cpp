#include "Utils.hpp"

#include <algorithm>

namespace Utils
{
	std::string ToLower(std::string str)
	{
		std::transform(std::begin(str), std::end(str), std::begin(str),
			[](unsigned char c) { return std::tolower(c); });

		return str;
	}

	bool HasWhitespaces(const std::string& flag)
	{
		return flag.find(' ') != std::string::npos;
	}
}