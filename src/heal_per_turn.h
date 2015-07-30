#ifndef BUFFS_HEAL_PER_TURN_H_
#define BUFFS_HEAL_PER_TURN_H_

#include "main.h"

class Character;

using namespace std;

class HealPerTurn : public Buff
{
	public:
		HealPerTurn(float power, int unique, int turns_total, string name);

		bool Update(Character& self);
};


#endif
