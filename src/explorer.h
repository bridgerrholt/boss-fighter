#ifndef EXPLORER_H_
#define EXPLORER_H_

#include "main.h"

class Game;

using namespace std;

class Explorer
{
	public:
		Explorer();
		~Explorer();

		vector<string> SeparateInput(string input);									// explodes at spaces
		void Explore(Game& game);													// takes input
		void ListCommands();														// prints all the commands
		void ListGenerations(Game& game, vector<string> input);						// prints all the commands
		void Stash(Game& game);
		string ReadCharacterData(Game& game, vector<vector<Character> >::iterator generation, vector<Character>::iterator character);
		bool TieBreakers(vector<float> results_1, vector<float> results_2);

		void Fight(Game& game, bool show_text);										// all the fighting and evolving
		void Battle(Game& game,														// a single fight between two characters
			Character& player1, Character& player2, int& winner, bool show_text);


	private:
		vector<vector<string> > commands_;

};

#endif
