#include "..\main.h"

GuardianHealer::GuardianHealer() : Ability()
{
	cost_ = 8;
	power_ = 20;
	name_ = "Healer Gaurdian";
	sentence_ = "summons a Healer Gaurdian!";
}

bool GuardianHealer::Use(Character& self, Character& enemy, int& cost)
{
	cost = cost_;

	if (self.magic() >= cost) {
		self.MagicDec(cost_);
		self.BuffsAdd(make_shared<HealPerTurn>(power_, 1, 3, name_));

		return true;
	}
	return false;
}