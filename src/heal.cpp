#include "main.h"

Heal::Heal(): Ability()
{
	cost_ = 8;
	power_ = 50;
	name_ = "Heal";
	sentence_ = "casts Heal!";
}

bool Heal::Use(Character& self, Character& enemy, int& cost)
{
	cost = cost_;

	if (self.magic() >= cost) {
		self.HealthInc(power_);
		self.MagicDec(cost_);

		return true;
	}
	return false;
}