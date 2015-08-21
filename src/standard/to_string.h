#ifndef STANDARD_TO_STRING_H_
#define STANDARD_TO_STRING_H_

#include "../main.h"

namespace Standard
{

	using namespace std;

	template <typename T>
	string to_string(const T& n)
	{
		stringstream stm;
		stm << n;
		return stm.str();
	}

}

#endif
