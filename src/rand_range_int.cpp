#include "main.h"

using namespace std;

int RandRangeInt(int min, int max) {
	return min + ((long int)rand())*(max-min) / (RAND_MAX+1.0);
}

int RandRangeInt(int max)
{
	return ((long int)rand())*max / (RAND_MAX+1.0);
}