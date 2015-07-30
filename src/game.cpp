#include "main.h"

using namespace std;

Game::Game()
{
	explorer = Explorer();

	abilities.push_back(make_unique<BattleCry>());
	abilities_map["BattleCry"] = abilities.size() - 1;
	abilities.push_back(make_unique<Heal>());
	abilities_map["Heal"] = abilities.size() - 1;
	abilities.push_back(make_unique<Hack>());
	abilities_map["Hack"] = abilities.size() - 1;
	abilities.push_back(make_unique<GuardianHealer>());
	abilities_map["Guardian Healer"] = abilities.size() - 1;
	/*abilities.push_back(make_unique<GuardianHealer>());
	abilities_map["GuardianHealer"] = abilities.size() - 1;*/
	boss_average_health_max = 0.0f;
	boss_average_magic_max = 0.0f;

	generation_amount = 0;
	character_amount = 100;
	//generation_results.push_back({});
	generation_results = vector<vector<vector<float> > >();

	mutation_start = 2;
	mutation_current = mutation_start;

	seed = time(NULL);
	srand(seed);
}