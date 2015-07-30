#include "main.h"

void Fight(Character& player1, Character& player2, Game& game)
{
/*	for (unsigned int i = 0; i < game.generation_amount; ++i) {
		for (auto j = game.generations[i].begin(); j != game.generations[i].end(); ++j) {
			game.generation_results.push_back({});
			string input;
			bool fighting = true;
			while (fighting) {
				//int player1_health = player1.health();
				int player2_health = player2.health();
				int player1_health = j->health();

#ifdef USING_COUT_
				cout << "Player 1:  " << player1_health << "/" << player1.health_max() << " HP  " <<
					player1.magic() << "/" << player1.magic_max() << " MP\n";
				cout << "Player 2:  " << player2_health << "/" << player2.health_max() << " HP  " <<
					player2.magic() << "/" << player2.magic_max() << " MP\n";

				if (player1_health <= 0 && player2_health <= 0) {
					cout << "\nIt's a tie!\n" << endl;
					fighting = false;
					break;
				} else if (player1_health <= 0) {
					cout << "\nPlayer 2 wins!\n" << endl;
					fighting = false;
					break;
				} else if (player2_health <= 0) {
					cout << "\nPlayer 1 wins!\n" << endl;
					fighting = false;
					break;
				}

				//cin >> input;
				input = cin.get();

				cout << "Player 1 ";
				player1.Fight(player2, game);
				cout << "\nPlayer 2 ";
				player2.Fight(player1, game);

				cout << "\n" << endl;
#else
				if (player1_health <= 0 && player2_health <= 0) {
					cout << "It's a tie!\n" << endl;
					fighting = false;
				} else if (player1_health <= 0) {
					cout << "Player 2 wins!\n" << endl;
					fighting = false;
				} else if (player2_health <= 0) {
					cout << "Player 1 wins!\n" << endl;
					fighting = false;
				}

				if (fighting == false) {
					game.generation_results[i].push_back({float(player1_health), float(player2_health)});
					break;
				} else {
					j->Fight(player2, game);
					player2.Fight(*j, game);
				}
#endif
			}
		}
	}*/
}