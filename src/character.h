#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "main.h"

struct Game;

using namespace std;

class Character
{
	public:
		Character();
		~Character();

		void Mutate(const Character& parent, const Game& game);
		void GenerateItemsSpecifics();
		void Reset();

		void PrintMoves();
		void Fight(Character& enemy, Game& game, bool show_text);
		void Attack(int ability_index, Character& enemy, Game& game, bool show_text);
		void AttackText(int ability_index, Character& enemy, Game& game);
		void UpdateBuffs(bool show_text, string name);
		bool EvaluateStatement(vector<vector<int> > statement, Character& enemy);
		string ReadStatement(vector<vector<int> > statement);
		string ReadAbility(Game& game, int ability);
		unsigned int CountStuff();

		void HealthInc(int amount);
		void HealthDec(int amount);
		void MagicDec(int amount);
		void AttackInc(int amount);
		void BuffsAdd(shared_ptr<Buff> buff);									// overwrites the one with the least time remaining if maximum amount (unique) is reached

		void SetStats(int health_max, int magic_max,
			int attack, int attack_min, int attack_max);

		int health() const { return health_; }
		int health_max() const { return health_max_; }
		int magic() const { return magic_; }
		int magic_max() const { return magic_max_; }
		int attack() const { return attack_; }
		int attack_min() const { return attack_min_; }
		int attack_max() const { return attack_max_; }
		vector<float> battle_results() const { return battle_results_; }
		vector<Item> items() const { return items_; }
		vector<int> abilities() const { return abilities_; }
		vector<shared_ptr<Buff> > buffs() const { return buffs_; }

		void health_set(int health) { health_ = health; }
		void health_max_set(int health_max) { health_max_ = health_max; }
		void magic_set(int magic) { magic_ = magic; }
		void magic_max_set(int magic_max) { magic_max_ = magic_max; }
		void battle_results_set(vector<float> battle_results) { battle_results_ = battle_results; }

		void attack_set(int attack) { attack_ = attack; }
		void attack_max_set(int attack_max) { attack_max_ = attack_max; }
		void attack_starting_set(int attack_starting) { attack_starting_ = attack_starting; }

		void items_set(vector<Item> items) { items_ = items; }
		void abilities_set(vector<int> abilities) { abilities_ = abilities; }


	private:


		vector<Item> items_;
		vector<shared_ptr<Buff> > buffs_;										// all the currently active buffs

		int health_max_, health_;
		int magic_max_, magic_;
		int attack_, attack_min_, attack_max_, attack_starting_;

		int current_item_;
		int current_item_move_;

		vector<int> abilities_;										// the abilities this character knows
		vector<float> battle_results_;								// [if passed on, health_, enemy.health(), magic_, enemy.magic(), amount of stuff]
};

#endif
