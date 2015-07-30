#ifndef ABILITIES_HEAL_H_
#define ABILITIES_HEAL_H_

#include "main.h"

class Character;

using namespace std;

class Heal: public Ability
{
	public:
		Heal();

		bool Use(Character& self, Character& enemy, int& cost);
};


#endif
