#include "main.h"

using namespace std;

int RandRangeInt(int min, int max) {
  return (int)floor(min + double(rand()*(max - min)) / double(RAND_MAX + 1.0));
}

int RandRangeInt(int max)
{
	return (int)floor(double(rand()*max) / double((RAND_MAX + 1.0)));
}