#include "main.h"

using namespace std;

Explorer::Explorer()
{
	commands_.push_back({"help", "list commads"});
}

Explorer::~Explorer()
{

}

vector<string> Explorer::SeparateInput(string input)
{
	vector<string> result;
	string current = "";

	for (auto i = input.begin(); i < input.end(); ++i) {
		if (*i == ' ') {
			if (current != "") {
				result.push_back(current);
				current = "";
			}
		} else {
			current += *i;
		}
	}

	if (current != "") {
		result.push_back(current);
		current = "";
	}

	return result;
}

void Explorer::Explore(Game& game)
{
	cout << '"' << "help" << '"' << " for the list of commands\n";

	//cout << "A1\n";

	bool done = false;
	while (done == false) {
		cout << ">>> ";
		//cout << "A2\n";
		//string input_raw;
		//cin >> input_raw;
		//char input_raw[65];			// can enter 64
		//cin.getline(input_raw, sizeof(input_raw));
		string input_raw;
		int input_int;
		getline(cin, input_raw);
		//cout << input_raw;
		//cout << "A5\n";

		/*cin.clear();														// sets the state back to good
		cin.ignore(numeric_limits<streamsize>::max(), '\n');*/				// clears the stream


		transform(input_raw.begin(), input_raw.end(), input_raw.begin(), ::tolower);
		vector<string> input = SeparateInput(input_raw);

		if (input.size() > 0)
			printf("\n");

		auto i = input.begin();
		//cout << "B1\n";

		if (i != input.end()) {
			if (*i == "help" || *i == "h") {
				ListCommands();

			} else if (*i == "quit" || *i == "q") {
				done = true;
				break;

			} else if (*i == "fight" || *i == "f") {
				if (next(i) != input.end()) {
					input_int = stoi(*next(i));
				} else {
					cout << "How many generations? ";

					while (!(cin >> input_int) || input_int < 0) {					// checks if it has an integer
						cout << "Must be an integer, enter again: ";
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				game.generation_amount = abs(input_int);

				Fight(game, false);

			} else if (*i == "generations" || *i == "g") {
				ListGenerations(game, input);
			}
		}

		//cout << endl;

	}
}

void Explorer::ListCommands()
{
	/*for (auto i = commands_.begin(); i != commands_.end(); ++i) {
		cout << *i->begin() << "   " << *next(i->begin()) << "\n";
	}*/

	//       0   1   2   3   4   5
	cout << "H-help              list commands"					<< '\n'
	     << "Q-quit              exit the program"				<< '\n'
	     << "F-fight <>          begin the fighting"			<< '\n'
		 << "    generation_amount"								<< '\n'
	     << "G-generations <>"									<< '\n'
	     << "    list"											<< '\n'
	     << "        results"									<< '\n'
		 << "        items"										<< '\n'
		 << "    stash"											<< '\n'
		 << "    fight <> <>"									<< '\n'
		 << "        generation character"						<< '\n'
		 ;
	cout << endl;
}

void Explorer::ListGenerations(Game &game, vector<string> input)
{
	auto i = input.begin();
	++i;
	if (i != input.end()) {
		if (*i == "list" || *i == "l") {
			++i;
			if (i != input.end()) {
				if (*i == "results" || *i == "r") {
					for (auto j = game.generations.begin(); j != game.generations.end(); ++j) {
						cout << "Generation " << (j - game.generations.begin()) << '\n';
						for (auto k = j->begin(); k != j->end(); ++k) {
							cout << " " << k->battle_results()[1] << " to " << k->battle_results()[2] << '\n';
						}
						cout << '\n';
					}
				} else if (*i == "items" || *i == "i") {
					for (auto j = game.generations.begin(); j != game.generations.end(); ++j) {
						cout << "Generation " << (j - game.generations.begin()) << '\n';
						for (auto k = j->begin(); k != j->end(); ++k) {
							k->PrintMoves();
						}
						cout << '\n';
					}
				}
			}
		} else if (*i == "stash" || *i == "s") {
			Stash(game);
		} else if (*i == "fight" || *i == "f") {
			int generation;

			++i;
			if (i != input.end()) {
				generation = stoi(*i);

				if (generation >= 0 && generation < game.generations.size()) {
					auto gen = game.generations.begin() + generation;

					int character;

					++i;
					if (i != input.end()) {
						character = stoi(*i);

						if (character >= 0 && character < gen->size()) {
							auto chr = gen->begin() + character;

							for (auto j = game.bosses.begin(); j != game.bosses.end(); ++j) {
								chr->Reset();
								j->Reset();
								int winner;
								Battle(game, *chr, *j, winner, true);
							}
						}
					}
				}
			}
		}
	}
}

void Explorer::Stash(Game& game)
{
	string description = "";
	description += "Seed:        " + to_string(game.seed) + "\n";
	description += "Generations: " + to_string(game.generation_amount) + "\n";
	description += "Population:  " + to_string(game.character_amount) + "\n\n";
	description += "The first generation is a single, pre-made character.\n";
	description += "The only things that change are the different movesets.\n";
	description += "The character chooses which move to use next based off which moveset statements are both true and most specific.\n";
	description += "If multiple moveset statements are equally specific, the higher one is used.\n";
	description += "Fallbacks (statements that are simply \"true\") have no value.\n";
	description += "Nothing in the battles are random, the only random factor is the mutations to each character (other than the first).\n";

	string dir = "stash/";
	string suffix = "-stash-all.txt";
	int prefix = 0;
	string prefix_str = FillTextWith(to_string(prefix), 4, '0');
	string file_name = dir + prefix_str + suffix;

	while (CheckFileExists(file_name)) {
		++prefix;
		prefix_str = FillTextWith(to_string(prefix), 4, '0');
		file_name = dir + prefix_str + suffix;
	}



	ofstream file;
	file.open(file_name);

	file << description;
	file << "These are all the individual characters.\n\n";

	for (auto i = game.generations.begin(); i != game.generations.end(); ++i) {
		file << "Generation " << i - game.generations.begin() << "\n";
		file << "-----------------\n";

		for (auto j = i->begin(); j != i->end(); ++j) {

			file << ReadCharacterData(game, i, j);

			/*file << " Character " << i - game.generations.begin() << ":" << j - i->begin() << " (" <<
				j->battle_results()[1] << "/" << j->health_max() << " HP, " <<
				j->battle_results()[3] << "/" << j->magic_max() << " MP) | Boss (" <<
				j->battle_results()[2] << "/" << game.boss.health_max() << " HP, " <<
				j->battle_results()[4] << "/" << game.boss.magic_max() << " MP)\n";

			file << "  Move sets:\n";
			auto items = j->items();
			for (auto k = items.begin(); k != items.end(); ++k) {
				file << "   " << j->ReadStatement((*k).statement) << "\n";
				for (auto a = k->moves.begin(); a != k->moves.end(); ++a) {
					file << "    " << j->ReadAbility(game, *a) << "\n";
				}
			}

			file << "\n";*/
		}

		file << "-----------------\n\n";
	}

	file.close();



	dir = "stash/";
	suffix = "-stash-best.txt";
	file_name = dir + prefix_str + suffix;


	file = ofstream();
	file.open(file_name);

	file << description;

	file << "These are the best characters in each generation.\n\n";
	file << "-- PASSED ON (only the ones that were BETTER than the previous get passed on) --\n\n";

	for (auto i = game.generations.begin(); i != game.generations.end(); ++i) {
		auto j = i->begin() + *(game.generation_winners.begin() + (i - game.generations.begin()));
		if (!(j->battle_results()[0] == 1 && i - game.generations.begin() != 0)) {
			file << "Generation " << i - game.generations.begin() << "\n";
			file << "-----------------\n";

			file << ReadCharacterData(game, i, j);

			/*file << " Complexity: " << j->battle_results()[5] << "\n";
			file << " Character " << i - game.generations.begin() << ":" << j - i->begin() << " (" <<
				j->battle_results()[1] << "/" << j->health_max() << " HP, " <<
				j->battle_results()[3] << "/" << j->magic_max() << " MP) | Boss (" <<
				j->battle_results()[2] << "/" << game.boss.health_max() << " HP, " <<
				j->battle_results()[4] << "/" << game.boss.magic_max() << " MP)";


			file << "\n";

			file << "  Move sets:\n";
			auto items = j->items();
			for (auto k = items.begin(); k != items.end(); ++k) {
				file << "   " << j->ReadStatement((*k).statement) << "\n";
				for (auto a = k->moves.begin(); a != k->moves.end(); ++a) {
					file << "     " << j->ReadAbility(game, *a) << "\n";
				}
			}

			file << "\n";*/

			file << "-----------------\n\n";
		}
	}

	file << "----------------------------------------------------------------------------------\n";
	file << "-- ALL --\n\n";

	for (auto i = game.generations.begin(); i != game.generations.end(); ++i) {
		file << "Generation " << i - game.generations.begin() << "\n";
		file << "-----------------\n";


		auto j = i->begin() + *(game.generation_winners.begin() + (i - game.generations.begin()));
		file << ReadCharacterData(game, i, j);


		/*file << " Character " << i - game.generations.begin() << ":" << j - i->begin() << " (" <<
			j->battle_results()[1] << "/" << j->health_max() << " HP, " <<
			j->battle_results()[3] << "/" << j->magic_max() << " MP) | Boss (" <<
			j->battle_results()[2] << "/" << game.boss.health_max() << " HP, " <<
			j->battle_results()[4] << "/" << game.boss.magic_max() << " MP)";

		if (j->battle_results()[0] == 1 && i - game.generations.begin() != 0)
			file << " NOT PASSED ON";

		file << "\n";

		file << "  Move sets:\n";
		auto items = j->items();
		for (auto k = items.begin(); k != items.end(); ++k) {
			file << "   " << j->ReadStatement((*k).statement) << "\n";
			for (auto a = k->moves.begin(); a != k->moves.end(); ++a) {
				file << "     " << j->ReadAbility(game, *a) << "\n";
			}
		}

		file << "\n";*/

		file << "-----------------\n\n";
	}

	file.close();

	/*ofstream file;
	file.open("stash.xml");

	file <<
		"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" <<
		"<data>\n" <<
			"<seed>" << "Seed: " << game.seed << "</seed>\n";

	for (auto i = game.generations.begin(); i != game.generations.end(); ++i) {

		file << "<generation-" << i - game.generations.begin() << ">\n";

		for (auto j = i->begin(); j != i->end(); ++j) {
			file << "<character-" << j - i->begin() + 1 << ">\n";

			file << "<results>" << j->battle_results()[1] << "hp to " << j->battle_results()[2] << "hp</results>\n";
			file << "<move-sets>\n";
			auto items = j->items();
			for (auto k = items.begin(); k != items.end(); ++k) {
				file << "<move-set>\n";
				file << "<statement>" << j->ReadStatement((*k).statement) << "</statement>\n";
				file << "<moves>\n";
				for (auto a = k->moves.begin(); a != k->moves.end(); ++a) {
					file << "<move>" << j->ReadAbility(*a) << "</move>\n";
				}
				file << "</moves>\n";
				file << "</move-set>\n";
			}
			file << "</move-sets>\n";

			file << "</character-" << j - i->begin() + 1 << ">\n";
		}

		file << "</generation-" << i - game.generations.begin() << ">\n";
	}

	file << "</data>";

	file.close();*/

	cout << "Done\n\n";
}

string Explorer::ReadCharacterData(Game& game, vector<vector<Character> >::iterator generation, vector<Character>::iterator character)
{
	int place = 0;
	int gen_id = generation - game.generations.begin();
	int char_id = character - generation->begin();
	vector<float> battle_results = character->battle_results();
	string text = "";

	// generation:character ... | ~passed_on
	string gen_and_char = "  " + to_string(gen_id) + ":" + to_string(char_id);


	// (hp/hp_max mp/mp_max) ... | Character
	// (hp/hp_max mp/mp_max) ... | Bosses
	string char_hp_1 = RoundToPlace(battle_results[1], place);
	string boss_hp_1 = RoundToPlace(battle_results[2], place);

	// make the same length
	while (char_hp_1.length() > boss_hp_1.length())
		boss_hp_1 = " " + boss_hp_1;
	while (char_hp_1.length() < boss_hp_1.length())
		char_hp_1 = " " + char_hp_1;

	string char_hp = char_hp_1 + "/" + RoundToPlace(character->health_max(), place);
	string boss_hp = boss_hp_1 + "/" + RoundToPlace(game.boss_average_health_max, place);

	// make the same length
	while (char_hp.length() > boss_hp.length())
		boss_hp += " ";
	while (char_hp.length() < boss_hp.length())
		char_hp += " ";

	string char_mp_1 = RoundToPlace(battle_results[3], place);
	string boss_mp_1 = RoundToPlace(battle_results[4], place);

	// make the same length
	while (char_mp_1.length() > boss_mp_1.length())
		boss_mp_1 = " " + boss_mp_1;
	while (char_mp_1.length() < boss_mp_1.length())
		char_mp_1 = " " + char_mp_1;

	string char_mp = char_mp_1 + "/" + RoundToPlace(character->magic_max(), place);
	string boss_mp = boss_mp_1 + "/" + RoundToPlace(game.boss_average_magic_max, place);

	// make the same length
	while (char_mp.length() > boss_mp.length())
		boss_mp += " ";
	while (char_mp.length() < boss_mp.length())
		char_mp += " ";


	string char_row = " (" + char_hp + " HP, " + char_mp + " MP)";
	string boss_row = " (" + boss_hp + " HP, " + boss_mp + " MP)";

	while (gen_and_char.length() < char_row.length())
		gen_and_char += " ";
	while (gen_and_char.length() > char_row.length()) {
		char_row += " ";
		boss_row += " ";
	}

	text += gen_and_char + " | ";
	if (battle_results[0] == 1.0f && gen_id != 0)
		text += "~NOT PASSED ON";
	else
		text += "~PASSED ON";

	text +=
		"\n" + char_row + " | Character" +
		"\n" + boss_row + " | Bosses" +
		"\n  Complexity: " + to_string(int(round(battle_results[5]))) +
		"\n  Move Sets:";

	auto items = character->items();
	for (auto i = items.begin(); i != items.end(); ++i) {
		text += "\n    " + character->ReadStatement((*i).statement);
		for (auto j = i->moves.begin(); j != i->moves.end(); ++j) {
			text += "\n      " + character->ReadAbility(game, *j);
		}
	}

	text += "\n\n";
	



	//file << " Character " << j - i->begin() << ": " << j->battle_results()[1] << "hp to " << j->battle_results()[2] << "hp | " <<
	//	j->battle_results()[3] << "mp to " << j->battle_results()[4] << "mp\n";


	return text;
}

void Explorer::Fight(Game& game, bool show_text)
{

	for (unsigned int i = 0; i < game.generation_amount; ++i) {
		vector<vector<float> > temp_results;
		if (i > 0) {
			vector<Character> temp;
			for (unsigned int j = 0; j < game.character_amount; ++j) {
				temp.push_back(Character());
				temp_results.push_back({});
			}
			game.generations.push_back(temp);
		} else {
			temp_results.push_back({});
		}
		game.generation_results.push_back(temp_results);
	}


	int winner = 0;			// 0: tie,  1: player1,  2: player2
	int mutation_inc_base = 10;

	//int best_character;
	vector<Character>::iterator best_character;
	vector<Character>::iterator best_character_last;
	auto i = game.generations.begin();
	best_character = i->begin();
	best_character_last = i->begin();
	auto ii = game.generation_results.begin();
	while (i != game.generations.end() && ii != game.generation_results.end()) {
		best_character = i->begin();

		if (i - game.generations.begin() > 0 &&
			(i - game.generations.begin()) % mutation_inc_base == 0) {
				++game.mutation_current;
		}
		

		for (auto j = i->begin(); j != i->end(); ++j) {
			if (i - game.generations.begin() != 0) {
				j->abilities_set(best_character_last->abilities());
				j->items_set(best_character_last->items());
				j->Mutate(*best_character_last, game);
				j->GenerateItemsSpecifics();
			}

			vector<vector<float> > temps = {{}, {}, {}, {}, {}, {}};
			for (auto k = game.bosses.begin(); k != game.bosses.end(); ++k) {
				j->Reset();
				Battle(game, *j, *k, winner, show_text);
				temps[0].push_back(1.0f);
				temps[1].push_back(float(j->health()));
				temps[2].push_back(float(k->health()));
				temps[3].push_back(float(j->magic()));
				temps[4].push_back(float(k->magic()));
				temps[5].push_back(float(j->CountStuff()));
			}

			vector<float> temp;
			for (auto i = temps.begin(); i != temps.end(); ++i) {
				temp.push_back(GetAverage(*i));
			}
			//vector<float> temp = {1.0f, float(j->health()), float(game.bosses[0].health()), float(j->magic()), float(game.bosses[0].magic()), float(j->CountStuff())};
			j->battle_results_set(temp);

			if (TieBreakers(j->battle_results(), best_character->battle_results())) {
				best_character = j;
			}

			/*if (j->battle_results()[2] < best_character->battle_results()[2]) {								// if enemy health is less than best
				best_character = j;

			} else if (j->battle_results()[2] == best_character->battle_results()[2]) {						// if enemy health is equal to best
				if (j->battle_results()[1] > best_character->battle_results()[1]) {							//   if character health is greater than best
					best_character = j;

				} else if (j->battle_results()[1] == best_character->battle_results()[1]) {					//   if character health is equal to best
					if (j->battle_results()[5] < best_character->battle_results()[5]) {						//     if character is simpler than best
						best_character = j;

					} else if (j->battle_results()[5] == best_character->battle_results()[5]) {				//   if character is as simple as best
						if (j->battle_results()[3] > best_character->battle_results()[3]) {					//     if character magic is greater than best
							best_character = j;

						} else if (j->battle_results()[3] == best_character->battle_results()[3]) {			//     if character magic is equal to best
							if (j->battle_results()[4] > best_character->battle_results()[4]) {				//       if enemy magic is greater than best
								best_character = j;
							}
						}
					}
				}
			}*/


			ii->push_back(temp);
			for (auto k = game.bosses.begin(); k != game.bosses.end(); ++k) {
				k->Reset();
			}
		}

		//int better = false;

		vector<float> best_results = best_character->battle_results();
		vector<float> last_results = best_character_last->battle_results();


		bool better = TieBreakers(best_results, last_results);
		//better = true;

		if (!better) {
			vector<float> battle_results = best_character->battle_results();
			battle_results[0] = 1.0f;
			best_character->battle_results_set(battle_results);
		} else {
			vector<float> battle_results = best_character->battle_results();
			battle_results[0] = 0.0f;
			best_character->battle_results_set(battle_results);
			best_character_last = best_character;
		}

		game.generation_winners.push_back(best_character - i->begin());

		/*for (auto k = ii->begin(); k != ii->end(); ++k) {
			if (*(k->begin() + 2) < *((ii->begin() + best_character)->begin() + 2)) {
				best_character = k - ii->begin();
			}
		}*/

		printf("Generation %d complete\n", i - game.generations.begin());

		++i;
		++ii;
	}

	printf("\nDone\n\n");
}

bool Explorer::TieBreakers(vector<float> results_1, vector<float> results_2)
{
	vector<vector<float> > order = {
		{results_1[2], results_2[2]},			// 1[enem.health] < 2[enem.health]
		{results_2[1], results_1[1]},			// 1[char.health] > 2[char.health]
		{results_1[5], results_2[5]},			// 1[complexity ] < 2[complexity ]
		{results_2[3], results_1[3]},			// 1[char.magic ] > 2[char.magic ]
		{results_2[4], results_1[4]}			// 1[enem.magic ] > 2[enem.magic ]
	};

	//bool result = false;


	for (auto i = order.begin(); i != order.end(); ++i) {
		if ((*i)[0] < (*i)[1])
			return true;
		else if ((*i)[0] > (*i)[1])
			break;
	}

	/*if (results_1[2] < results_2[2]) {								// if enemy health is less than best
		return true;

	} else if (results_1[2] == results_2[2]) {						// if enemy health is equal to best
		if (results_1[1] > results_2[1]) {							//   if character health is greater than best
			return true;

		} else if (results_1[1] == results_2[1]) {					//   if character health is equal to best
			if (results_1[5] < results_2[5]) {						//     if character is simpler than best
				return true;

			} else if (results_1[5] == results_2[5]) {				//   if character is as simple as best
				if (results_1[3] > results_2[3]) {					//     if character magic is greater than best
					return true;

				} else if (results_1[3] == results_2[3]) {			//     if character magic is equal to best
					if (results_1[4] > results_2[4]) {				//       if enemy magic is greater than best
						return true;
					}
				}
			}
		}
	}*/

	return false;
}

void Explorer::Battle(Game& game, Character& player1, Character& player2, int& winner, bool show_text)
{
	//game.generation_results.push_back({});
	string input;
	bool fighting = true;
	while (fighting) {
		//int player1_health = player1.health();
		int player1_health = player1.health();
		int player2_health = player2.health();

		if (show_text) {
			//printf("Player 1: %d/%d HP  %d/%d MP\n", player1_health, player1.health_max(), player1.magic(), player1.magic_max());
			//printf("Player 2: %d/%d HP  %d/%d MP\n", player2_health, player2.health_max(), player2.magic(), player2.magic_max());
			printf("Player 1: %d/%d HP  %d/%d MP\nPlayer 2: %d/%d HP  %d/%d MP",
				player1_health, player1.health_max(), player1.magic(), player1.magic_max(),
				player2_health, player2.health_max(), player2.magic(), player2.magic_max());

			input = cin.get();
		}

		if (player1_health <= 0 && player2_health <= 0) {
			if (show_text)
				printf("It's a tie!\n\n");
			winner = 0;
			fighting = false;
		} else if (player1_health <= 0) {
			if (show_text)
				printf("Player 2 wins!\n\n");
			winner = 2;
			fighting = false;
		} else if (player2_health <= 0) {
			if (show_text)
				printf("Player 1 wins!\n\n");
			winner = 1;
			fighting = false;
		}

		if (fighting == false) {
			//game.generation_results[i].push_back({player1_health, player2_health});
			break;
		} else {


			if (show_text)
				printf("\nPlayer 1 ");
			player1.Fight(player2, game, show_text);

			if (show_text)
				printf("\nPlayer 2 ");
			player2.Fight(player1, game, show_text);

			if (player1.health() > 0 && player2.health() > 0) {
				player1.UpdateBuffs(show_text, "Player 1");
			}

			if (player1.health() > 0 && player2.health() > 0) {
				player2.UpdateBuffs(show_text, "Player 2");
			}

			if (show_text)
				printf("\n\n");
		}
	}
}
