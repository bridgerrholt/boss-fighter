#include "../main.h"

int Standard::stoi(const std::string& str, std::size_t* pos, int base)
{
	const char* begin = str.c_str();
	char* end = nullptr;
	long value = std::strtol(begin, &end, base);

	if (errno == ERANGE || value > std::numeric_limits<int>::max())
		throw std::out_of_range("Standard::stoi: out of range");

	if (end == str.c_str())
		throw std::invalid_argument("Standard::stoi: invalid argument");

	if (pos) *pos = end - begin;

	return value;
}