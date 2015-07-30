#include "main.h"

using namespace std;

int RandRangeInt(int min, int max) {
  return min + int((rand()*(max - min)) / (RAND_MAX + 1.0));
}

int RandRangeInt(int max)
{
	return rand()*max / (RAND_MAX + 1.0);
}