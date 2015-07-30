#include "main.h"

using namespace std;

 bool CheckFileExists(const string& name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}