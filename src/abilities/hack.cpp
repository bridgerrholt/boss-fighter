#include "../main.h"

Hack::Hack() : Ability()
{
	cost_ = 8;
	power_ = 2;
	name_ = "Hack";
	sentence_ = "uses Hack!";
}

bool Hack::Use(Character& self, Character& enemy, int& cost)
{
	cost = cost_;

	if (self.magic() >= cost) {
		enemy.HealthDec(power_*self.attack());
		self.MagicDec(cost_);

		return true;
	}
	return false;
}