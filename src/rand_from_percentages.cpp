#include "main.h"

using namespace std;

unsigned int RandRangePercentages(const vector<unsigned int>& percentages)
{
	unsigned int total = 0;
	for (auto i = percentages.begin(); i != percentages.end(); ++i) {
		total += *i;
	}

	unsigned int value = RandRangeInt(total);

	float current = 0.0f;
	for (auto i = percentages.begin(); i != percentages.end(); ++i) {
		current += *i;
		if (value < current)
			return i - percentages.begin();
	}

	return 0;
}