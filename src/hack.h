#ifndef ABILITIES_HACK_H_
#define ABILITIES_HACK_H_

#include "main.h"

class Character;

using namespace std;

class Hack: public Ability
{
	public:
		Hack();

		bool Use(Character& self, Character& enemy, int& cost);
};


#endif
