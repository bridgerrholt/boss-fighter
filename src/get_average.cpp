#include "main.h"

using namespace std;

float GetAverage(vector<int> data)
{
	int total = 0;
	for (auto i = data.begin(); i != data.end(); ++i) {
		total += *i;
	}

	return float(total) / float(data.size());
}

float GetAverage(vector<float> data)
{
	float total = 0;
	for (auto i = data.begin(); i != data.end(); ++i) {
		total += *i;
	}

	return total / float(data.size());
}