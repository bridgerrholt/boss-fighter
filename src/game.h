#ifndef GAME_H_
#define GAME_H_

#include "main.h"

//class Explorer;

using namespace std;

struct Game
{
	Game();

	Explorer explorer;

	vector<unique_ptr<Ability> > abilities;
	map<string, int> abilities_map;

	vector<Character> bosses;
	float boss_average_health_max;
	float boss_average_magic_max;

	int generation_amount;
	int character_amount;
	vector<vector<Character> > generations;

	/*
	[x]:		the specific generation
	[x][y]:		the specific character
	[x][y][0]:	ranking
	[x][y][1]:	character health
	[x][y][2]:	enemy health
	[x][y][3]:	character magic
	[x][y][4]:	enemy magic
	*/
	vector<vector<vector<float> > > generation_results;
	vector<int> generation_winners;

	unsigned int seed;
	unsigned int mutation_start;
	unsigned int mutation_current;									// how many things can change each mutation, goes up every few generations
};

#endif
