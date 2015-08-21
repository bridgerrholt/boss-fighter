#include "main.h"

using namespace std;

string RoundToPlace(float value, int place)
{
	if (value == 0.0f) {
		string text = "0";
		if (place > 0) {
			text += ".";
			for (unsigned int i = 0; i < place; ++i)
				text += "0";
		}

		return text;
	}

	value = round(value*pow(10, place));
	string text = Standard::to_string(int(value));

	if (place > 0) {
		text.insert(text.length() - place, ".");
	}

	return text;
}