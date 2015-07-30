#include "..\main.h"

HealPerTurn::HealPerTurn(float power, int unique, int turns_total, string name) : Buff()
{
	power_ = power;
	unique_ = unique;

	turns_total_ = turns_total;
	turns_left_ = turns_total_;
	dead_ = false;

	name_ = name;
	sentence_ = "was healed for " + to_string(int(round(power_))) + " by " + name + "!";
}

bool HealPerTurn::Update(Character& self)  // returns if still alive
{
	if (!dead_) {
		self.HealthInc(power_);

		--turns_left_;

		if (turns_left_ <= 0) {
			dead_ = true;
			return false;
		}

		return true;
	}

	return false;
}