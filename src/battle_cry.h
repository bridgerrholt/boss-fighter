#ifndef ABILITIES_BATTLE_CRY_H_
#define ABILITIES_BATTLE_CRY_H_

#include "main.h"

class Character;

using namespace std;

class BattleCry: public Ability
{
	public:
		BattleCry();

		bool Use(Character& self, Character& enemy, int& cost);
};


#endif
