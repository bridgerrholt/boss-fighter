#include "main.h"

using namespace std;

string FillTextWith(string text, int size, char fill)
{
	if (text.length() < size) {
		string result = "";

		for (unsigned int i = 0; i < size - text.length(); ++i) {
			result += fill;
		}

		return result + text;

	} else {
		return text;
	}

	return "";
}