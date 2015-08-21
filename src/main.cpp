#include "main.h"

int main(int argc, char *argv[])
{
	srand(time(NULL));

	Game game = Game();


	/*string input;
	cout << "How many generations? ";
	cin >> input;
	//game.generation_amount = abs(Standard::stoi(input));
	game.generation_amount = 5;
	cout << endl;
	cin.get();*/

	game.generations.push_back({Character()});
	//Character character = Character();
	game.bosses.push_back(Character());
	game.bosses.push_back(Character());
	game.bosses.push_back(Character());

	// abilities
	vector<int> abilities;
	abilities.push_back(game.abilities_map["BattleCry"] + 1);
	abilities.push_back(game.abilities_map["Heal"] + 1);
	abilities.push_back(game.abilities_map["Hack"] + 1);
	abilities.push_back(game.abilities_map["Guardian Healer"] + 1);

	game.generations[0][0].abilities_set(abilities);
	for (auto i = game.bosses.begin(); i != game.bosses.end(); ++i)
		i->abilities_set(abilities);


	// items
	// player
	vector<Item> items;
	Item temp_item = Item();
	/*temp_item.statement.push_back({4, 0});								// FALLBACK (true)
	temp_item.moves.push_back(0);										// Normal attack
	items.push_back(temp_item);

	temp_item = Item();
	temp_item.statement.push_back({0, 0, 30, 0});						// health_ <= 30%
	temp_item.moves.push_back(2);										// Heal
	items.push_back(temp_item);

	temp_item = Item();
	temp_item.statement.push_back({2, 1, 100, 0});						// enemy.health() >= 100%
	temp_item.moves.push_back(1);										// Battle Cry
	temp_item.moves.push_back(1);
	temp_item.moves.push_back(1);
	temp_item.moves.push_back(0);
	items.push_back(temp_item);

	game.generations[0][0].items_set(items);*/


	// boss 0
	items.clear();
	temp_item = Item();
	temp_item.statement.push_back({4, 0});								// FALLBACK (true)
	temp_item.moves.push_back(1);										// Battle Cry
	temp_item.moves.push_back(0);										// Normal attack
	temp_item.moves.push_back(0);
	temp_item.moves.push_back(0);
	temp_item.moves.push_back(0);
	temp_item.moves.push_back(0);
	temp_item.moves.push_back(0);
	temp_item.moves.push_back(0);
	temp_item.moves.push_back(0);
	items.push_back(temp_item);

	temp_item = Item();
	temp_item.statement.push_back({0, 0, 10, 0});						// health_ <= 30%
	temp_item.moves.push_back(2);										// Heal
	items.push_back(temp_item);

	game.bosses[0].items_set(items);

	// boss 1
	items.clear();
	temp_item = Item();
	temp_item.statement.push_back({4, 0});								// FALLBACK (true)
	temp_item.moves.push_back(4);										// Healer Guardian
	temp_item.moves.push_back(1);										// Battle Cry
	temp_item.moves.push_back(3);										// Hack
	temp_item.moves.push_back(0);
	temp_item.moves.push_back(0);
	items.push_back(temp_item);

	temp_item = Item();
	temp_item.statement.push_back({0, 0, 5, 0});						// health_ <= 5%
	temp_item.moves.push_back(2);										// Heal
	items.push_back(temp_item);

	game.bosses[1].items_set(items);

	// boss 2
	items.clear();
	temp_item = Item();
	temp_item.statement.push_back({4, 0});								// FALLBACK (true)
	temp_item.moves.push_back(3);										// Hack
	temp_item.moves.push_back(3);										// Hack
	temp_item.moves.push_back(0);										// Hack
	items.push_back(temp_item);

	temp_item = Item();
	temp_item.statement.push_back({0, 0, 70, 1, 0, 1, 40, 0});			// health_ <= 70% && >= 40%
	temp_item.moves.push_back(1);										// Battle Cry
	items.push_back(temp_item);

	game.bosses[2].items_set(items);


	// character 0:0
	items.clear();
	temp_item = Item();
	temp_item.statement.push_back({4, 0});								// FALLBACK (true)
	temp_item.moves.push_back(0);										// Normal attack
	items.push_back(temp_item);

	/*temp_item = Item();
	temp_item.statement.push_back({0, 0, 47, 1, 1, 1, 20, 0});			// health_ <= 30%
	temp_item.moves.push_back(4);										// Heal
	temp_item.moves.push_back(0);
	items.push_back(temp_item);

	temp_item = Item();
	temp_item.statement.push_back({2, 1, 100, 0});
	temp_item.moves.push_back(1);
	temp_item.moves.push_back(1);
	temp_item.moves.push_back(1);
	temp_item.moves.push_back(3);
	items.push_back(temp_item);*/
	/*temp_item = Item();
	temp_item.statement.push_back({0, 0, 30, 0});
	temp_item.moves.push_back(4);
	items.push_back(temp_item);*/

	game.generations[0][0].items_set(items);


	// stats
	//boss.attack_set(50);
	//boss.attack_starting_set(boss.attack());
	/*game.bosses[0].health_max_set(300);
	game.bosses[0].health_set(game.bosses[0].health_max());*/
	game.bosses[0].SetStats(300, game.bosses[0].magic_max(), game.bosses[0].attack(), game.bosses[0].attack_min(), game.bosses[0].attack_max());

	/*game.bosses[1].health_max_set(200);
	game.bosses[1].health_set(game.bosses[0].health_max());
	game.bosses[1].magic_max_set(100);
	game.bosses[1].magic_set(game.bosses[0].magic_max());*/
	game.bosses[1].SetStats(200, 100, 15, 10, 45);
	//boss.magic_max_set(200);
	//boss.magic_set(boss.magic_max());
	game.bosses[2].SetStats(250, 70, 10, 10, 100);


	game.generations[0][0].GenerateItemsSpecifics();
	for (auto i = game.bosses.begin(); i != game.bosses.end(); ++i) {
		i->GenerateItemsSpecifics();
	}

	//Fight(game.generations[0][0], game.boss, game);
	//ExploreResults();

	/*for (auto i = game.generation_results.begin(); i != game.generation_results.end(); ++i) {
		cout << "GENERATION " << i - game.generation_results.begin() + 1 << "\n";
		for (auto j = i->begin(); j != i->end(); ++j) {
			cout << " fight 1: ";
			cout << *j->begin() << " HP to;
			for (auto k = j->begin(); k != j->end(); ++k) {
				cout << *k << " ";
			}
			cout << "\n";
		}
	}*/

	vector<int> bosses_healths;
	vector<int> bosses_magics;

	for (auto i = game.bosses.begin(); i != game.bosses.end(); ++i) {
		bosses_healths.push_back(i->health_max());
		bosses_magics.push_back(i->magic_max());
	}

	//game.bosses.erase(game.bosses.begin());
	//game.bosses.erase(game.bosses.begin());
	//game.bosses.erase(game.bosses.end()-1);

	game.boss_average_health_max = GetAverage(bosses_healths);
	game.boss_average_magic_max = GetAverage(bosses_magics);

	game.explorer.Explore(game);

	//system("pause");
	return 0;
}