#ifndef TO_STRING_REC_H_
#define TO_STRING_REC_H_

#include "main.h"

using namespace std;

template <typename T>
string toStringRec(const T& n)
{
	stringstream stm;
	stm << n;
	return stm.str();
}

#endif
