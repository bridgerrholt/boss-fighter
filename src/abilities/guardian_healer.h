#ifndef ABILITIES_GUARDIAN_HEALER_H_
#define ABILITIES_GUARDIAN_HEALER_H_

#include "../main.h"

class Character;

using namespace std;

class GuardianHealer: public Ability
{
	public:
		GuardianHealer();

		bool Use(Character& self, Character& enemy, int& cost);
};


#endif
