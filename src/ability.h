#ifndef ABILITY_H_
#define ABILITY_H_

#include "main.h"

class Character;

using namespace std;

class Ability
{
	public:
		Ability();
		~Ability();

		virtual bool Use(Character& self, Character& enemy, int& cost);

		string name() const { return name_; }
		string sentence() const { return sentence_; }

	protected:
		float power_;
		float cost_;

		string name_;
		string sentence_;
};

#endif
