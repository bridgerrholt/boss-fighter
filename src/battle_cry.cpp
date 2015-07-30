#include "main.h"

BattleCry::BattleCry(): Ability()
{
	cost_ = 6;
	power_ = 8;
	name_ = "Battle Cry";
	sentence_ = "uses Battle Cry!";
}

bool BattleCry::Use(Character& self, Character& enemy, int& cost)
{
	cost = cost_;

	if (self.magic() >= cost) {
		self.AttackInc(power_);
		self.MagicDec(cost_);

		return true;
	}
	return false;
}