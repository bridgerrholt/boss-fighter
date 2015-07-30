#ifndef BUFF_H_
#define BUFF_H_

#include "main.h"

class Character;

using namespace std;

class Buff
{
	public:
		Buff();
		~Buff();

		virtual bool Update(Character& self);
		virtual void Kill();

		void name_set(string name) { name_ = name; }

		int unique() const { return unique_; }
		int turns_left() const { return turns_left_; }
		bool dead() const { return dead_; }
		string name() const { return name_; }
		string sentence() const { return sentence_; }


	protected:
		float power_;
		int unique_;												// how many can be on at the same time (but 0 means no limit)

		int turns_total_;
		int turns_left_;
		bool dead_;

		string name_;
		string sentence_;
};

#endif
