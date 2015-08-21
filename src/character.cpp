#include "main.h"

Character::Character()
{
	health_max_ = 100;
	health_ = health_max_;
	magic_max_ = 50;
	magic_ = magic_max_;
	attack_max_ = 40;
	attack_starting_ = 10;
	attack_ = attack_starting_;
	attack_min_ = 5;

	//abilities_ = abilities;
	//abilities_map_ = abilities_map;

	/*
		Item.statement:
			    | (health_ <= 20% && magic_ >= 8%) && (enemy.health() >= 50%) END
			[0] | [0]      [1][2] [3][4]    [5][6] [7] [8]            [9][10] [11]

			The rows have all the individual statements (the parenthesis)
			The columns have the information about what to check
			If you had a single statement, it would look like this:
				[0]: 0  health_
				     1  magic_
					 2  enemy.health()
					 3  enemy.magic()
					 4  true (special, it means this is a fallback)

				[1]: 0  <=
				     1  >=
					 2  ==
					 3  !=

				[2]: 0  value

				[3]: 0  END
				     1  &&
					 2  ||

			In the case of a fallback, only [0] and [3] are considered

			Example:
				(health_ <= 20% && magic >= 8%)  would be
				 0       0  20  1  1     1  8  0
				{0,      0, 20, 1, 1,    1, 8, 0}

			In all reality, the END is not really required, as it will only be used once in a full statement

			Another Example:
				(health_ >= 50% || magic >= 18%) && (enemy.health >= 50%)  would be
				 0       0  50  2  1     0  18   1   2            0  50  0
				{0,      0, 50, 2, 1,    0, 18,  1},{2,           0, 50, 0}
				
				Notice how the last column in a row says how to compare it to the next row

			A Fallback would work like:
				(true)
				 4    0
				{4,   0}
	
	*/

	//items_ = items;


	current_item_ = 0;
	current_item_move_ = 0;

	buffs_ = {};

	//GenerateItemsSpecifics();
}

Character::~Character()
{

}

void Character::Reset()
{
	health_ = health_max_;
	magic_ = magic_max_;
	attack_ = attack_starting_;

	current_item_ = 0;
	current_item_move_ = 0;
}

void Character::SetStats(int health_max, int magic_max,
	int attack, int attack_min, int attack_max)
{
	health_max_ = health_max;
	health_ = health_max_;

	magic_max_ = magic_max;
	magic_ = magic_max_;

	attack_ = attack;
	attack_starting_ = attack_;
	attack_min_ = attack_min;
	attack_max_ = attack_max;
}

void Character::Mutate(const Character& parent, const Game& game)
{
	int chance = 10;

	// 0: new moveset, 1: change percents, 2: add to movesets, 3: delete from movesets, 4: change parameter
	// 5: add to statements, 6: flip signs, 7: remove from statements
	vector<unsigned int> percentages =
		{8, 40, 25, 10, 30,
		15, 30, 15};
	percentages =
		{10, 10, 10, 10, 10,
		10, 10};
	//int choices_size = RandRangeInt(1, game.mutation_current);
	int choices_size = RandRangeInt(1, ceil(CountStuff()*0.5f));
	int choice = 0;


	/*if (items_.size() == 1) {
		choices.push_back(0);
		for (int i = 0; i < choices_size - 1; ++i) {
			choices.push_back(RandRangePercentages(percentages));
		}
	} else {
		for (int i = 0; i < choices_size; ++i) {
			choices.push_back(RandRangePercentages(percentages));
		}
	}*/

	for (unsigned int choice_looper = 0; choice_looper < choices_size; ++choice_looper) {
		// must be in the for loop, in case #3 deletes a moveset leaving only 1 Item remaining
		if (items_.size() == 1) {
			choice = 0;
		} else {
			choice = RandRangePercentages(percentages);
		}

		// 0: New Moveset (pushes a new Item)
		if (choice == 0) {
			Item temp_item;

			int statements_amount = RandRangeInt(1, 2);		// 1 statement

			for (unsigned int i = 0; i < statements_amount; ++i) {
				vector<int> statement;
				statement.push_back(RandRangeInt(0, 4));			// can't be a fallback
				if (statement[0] != 4) {							//   will always happen because it can't be a fallback
					statement.push_back(RandRangeInt(2));			//     <= or >=
					statement.push_back(RandRangeInt(101));			//     y%
				}

				if (i < statements_amount - 1) {					// if it's not the last one
					statement.push_back(RandRangeInt(1, 3));		//   && or ||
				} else {											// if it is the last one
					statement.push_back(0);							//   end
				}

				temp_item.statement.push_back(statement);
			}

			int moves_amount = RandRangeInt(1, 2);									// 1 move
			for (unsigned int i = 0; i < moves_amount; ++i) {
				temp_item.moves.push_back(RandRangeInt(abilities_.size() + 1));		// random move
			}

			items_.push_back(temp_item);  // commit it all

			GenerateItemsSpecifics();


		// 1: Change Percentages (adds or subtracts from a constant percentage)
		} else if (choice == 1) {
			vector<vector<int>::iterator> its;					// iterators back to the actual percents

			for (auto i = items_.begin(); i != items_.end(); ++i) {
				for (auto j = i->statement.begin(); j != i->statement.end(); ++j) {

					int pos = 0;
					for (auto k = j->begin(); k != j->end(); ++k) {
						if (pos == 0) {							// variables
							++pos;
							if (*k == 4) {						// if a fallback
								pos = 3;
							}
						} else if (pos == 1) {					// operators
							++pos;
						} else if (pos == 2) {					// percentages
							++pos;

							its.push_back(k);

						} else if (pos == 3) {					// gates/END
							pos = 0;
						}
					}
				}

			}


			auto i = its.begin() + RandRangeInt(its.size());
			int max = 40;
			int add = 0;

			/*if (**i - max < 0)			// if it would underflow
				add = 1;
				else if (**i + max > 100)	// if it would go above 100%
				add = 0;
				else
				add = RandRangeInt(2);*/
			add = RandRangeInt(2);

			if (add == 0) {
				**i -= RandRangeInt(1, max + 1);
				if (**i < 0)
					**i = 0;
			} else {
				**i += RandRangeInt(1, max + 1);
				if (**i > 100)
					**i = 100;
			}


		// 2: Add to Moveset (adds a move to a moveset)
		} else if (choice == 2) {

			auto moveset = items_.begin() + RandRangeInt(items_.size());					// points to a random Item

			auto position = moveset->moves.begin() + RandRangeInt(moveset->moves.size());	// points to a random position in the Item
			moveset->moves.insert(position, RandRangeInt(abilities_.size() + 1));			// inserts a random move at that position


		// 3: Delete From Moveset (deletes a move from a moveset, deletes the moveset if it's the last move)
		} else if (choice == 3) {
			vector<Item>::iterator moveset;					// points to a random Item

			if (items_.begin()->moves.size() <= 1) {							// if the first Item only has 1 move
				moveset = items_.begin() + RandRangeInt(1, items_.size());		//   don't point to it
			} else {															// if the first Item has more than 1 move
				moveset = items_.begin() + RandRangeInt(items_.size());			//   possibly point to it
			}



			if (moveset->moves.size() == 1) {										// if it only has 1 move
				items_.erase(moveset);												//   erase the whole Item
				GenerateItemsSpecifics();											//   re-generate the rankings for Items
			} else {																// if it has more than 1 move
				auto position = moveset->moves.begin() +							//   erase a random move
					RandRangeInt(moveset->moves.size());
			}


		// 4: Change a Parameter (changes a random parameter into something different)
		} else if (choice == 4) {
			vector<vector<int>::iterator> its;					// iterators back to the actual parameters

			for (auto i = items_.begin(); i != items_.end(); ++i) {
				for (auto j = i->statement.begin(); j != i->statement.end(); ++j) {

					int pos = 0;
					for (auto k = j->begin(); k != j->end(); ++k) {
						if (pos == 0) {								// variables
							if (*k == 4) {							// if a fallback
								pos = 3;
							} else {
								++pos;
								its.push_back(k);					// give the location within the statement (never a fallback)
							}
						} else if (pos == 1) {						// operators
							++pos;
						} else if (pos == 2) {						// percentages
							++pos;
						} else if (pos == 3) {						// gates/END
							pos = 0;
						}
					}
				}

			}

			auto i = its.begin() + RandRangeInt(its.size());

			int parameter = RandRangeInt(4);
			while (**i == parameter) {
				parameter = RandRangeInt(4);
			}

			**i = parameter;

			GenerateItemsSpecifics();


		// 5: Add to Statement (adds more to a random statement)
		} else if (choice == 5) {
			vector<vector<int>::iterator> its;					// iterators back to the actual statement endings
			vector<vector<vector<int> >::iterator> vecs;

			for (auto i = items_.begin(); i != items_.end(); ++i) {
				for (auto j = i->statement.begin(); j != i->statement.end(); ++j) {

					bool is_fallback = false;
					int pos = 0;
					for (auto k = j->begin(); k != j->end(); ++k) {
						if (pos == 0) {								// variables
							if (*k == 4) {							// if a fallback
								pos = 3;
								is_fallback = true;
							} else {
								++pos;
							}
						} else if (pos == 1) {						// operators
							++pos;
						} else if (pos == 2) {						// percentages
							++pos;
						} else if (pos == 3) {						// gates/END
							pos = 0;
							if (!is_fallback && *k == 0) {			// no fallbacks and only inserts at the end
								its.push_back(k);
								vecs.push_back(j);
							}
							is_fallback = false;
						}
					}
				}

			}

			int position = RandRangeInt(its.size());
			auto i = its.begin() + position;
			auto j = vecs.begin() + position;

			vector<int> new_statement = {RandRangeInt(4), RandRangeInt(2), RandRangeInt(101)};
			while (new_statement[0] == *(*i - 3) &&			// while it equals the same statement
				new_statement[1] == *(*i - 2) &&
				new_statement[2] == *(*i - 1)) {
				new_statement = {RandRangeInt(4), RandRangeInt(2), RandRangeInt(101)};
			}


			if (**i == 0) {		// if end
				**i = RandRangeInt(1, 3);				// && or ||
				(*j)->push_back(new_statement[0]);		// x
				(*j)->push_back(new_statement[1]);		// <= or >=
				(*j)->push_back(new_statement[2]);		// y%
				(*j)->push_back(0);						// end
			} else {
				printf("begin\n");
				(*j)->insert(*(its.begin() + position), new_statement[0]);		// x
				printf("a\n");
				(*j)->insert(*(its.begin() + position) + 1, new_statement[1]);		// <= or >=
				printf("b\n");
				(*j)->insert(*(its.begin() + position) + 2, new_statement[2]);		// y%
				printf("c\n");
				(*j)->insert(*(its.begin() + position) + 3, RandRangeInt(1, 3));	// && or ||
				printf("end\n");
			}

			GenerateItemsSpecifics();


		// 6: Flip Signs (flips a random operator from <= to >=, vice verse)
		} else if (choice == 6) {
			vector<vector<int>::iterator> its;					// iterators back to the actual operators

			for (auto i = items_.begin(); i != items_.end(); ++i) {
				for (auto j = i->statement.begin(); j != i->statement.end(); ++j) {

					int pos = 0;
					for (auto k = j->begin(); k != j->end(); ++k) {
						if (pos == 0) {							// variables
							++pos;
							if (*k == 4) {						// if a fallback
								pos = 3;
							}
						} else if (pos == 1) {					// operators
							++pos;

							its.push_back(k);
						} else if (pos == 2) {					// percentages
							++pos;
						} else if (pos == 3) {					// gates/END
							pos = 0;
						}
					}
				}

			}


			auto i = its.begin() + RandRangeInt(its.size());

			if (**i == 0)
				**i = 1;
			else
				**i = 0;


		//7: Remove From Statements (removes a statement from a random statement, doesn't delete if it's the last statement)
		} else if (choice == 7) {
			vector<vector<int>::iterator> its;					// iterators back to the actual statement endings
			vector<vector<vector<int> >::iterator> vecs;

			for (auto i = items_.begin(); i != items_.end(); ++i) {
				for (auto j = i->statement.begin(); j != i->statement.end(); ++j) {

					bool found_one = false;
					bool is_fallback = false;
					int pos = 0;
					for (auto k = j->begin(); k != j->end(); ++k) {
						if (pos == 0) {								// variables
							if (*k == 4) {							// if a fallback
								pos = 3;
								is_fallback = true;
							} else {
								++pos;
							}
						} else if (pos == 1) {						// operators
							++pos;
						} else if (pos == 2) {						// percentages
							++pos;
						} else if (pos == 3) {						// gates/END
							pos = 0;
							if (*k != 0) {							// if a gate
								found_one = true;
							}

							if ((!is_fallback) &&					// no fallbacks
								!(*k == 0 && !found_one)) {			// if not the END and only statement
								its.push_back(k);
								vecs.push_back(j);
							}

							is_fallback = false;
						}
					}
				}

			}

			if (its.size() > 0) {
				int position = RandRangeInt(its.size());
				auto i = its.begin() + position;
				auto j = vecs.begin() + position;

				if (**i == 0) {		// if end
					(*j)->erase((*i) - 4, (*i));
				} else {
					(*j)->erase((*i) - 3, (*i) + 1);
				}

				GenerateItemsSpecifics();
			} else {
				--choice_looper;
			}
		}
	}
}

void Character::GenerateItemsSpecifics()
{
	int pos = 0;
	for (auto i = items_.begin(); i != items_.end(); ++i) {						// go through all the items
		i->specific = 0;
		pos = 0;

		for (auto j = i->statement.begin(); j != i->statement.end(); ++j) {		// go through all the statements
			for (auto k = j->begin(); k != j->end(); ++k) {
				if (pos == 0) {
					++pos;
					if (*k == 0 || *k == 1)						// checking player health or magic
						i->specific += 2;
					else if (*k == 2 || *k == 3)				// checking enemy health or magic
						i->specific += 1;
					else if (*k == 4)							// always true/fallback, no value, skips the checking
						pos = 3;

				} else if (pos == 1) {
					++pos;
				} else if (pos == 2) {
					++pos;
				} else if (pos == 3) {
					pos = 0;
				}
			}
		}
	}
}

void Character::PrintMoves()
{
	string statement;
	int pos = 0;
	for (auto i = items_.begin(); i != items_.end(); ++i) {
		statement = "if (";
		pos = 0;

		for (auto j = i->statement.begin(); j != i->statement.end(); ++j) {
			statement += "(";
			for (auto k = j->begin(); k != j->end(); ++k) {
				if (pos == 0) {
					++pos;
					if (*k == 0) {
						statement += "health_";
					} else if (*k == 1) {
						statement += "magic_";
					} else if (*k == 2) {
						statement += "enemy.health()";
					} else if (*k == 3) {
						statement += "enemy.magic()";
					} else if (*k == 4) {
						statement += "true";
						pos = 3;
					}
				} else if (pos == 1) {
					++pos;
					if (*k == 0) {
						statement += " <= ";
					} else if (*k == 1) {
						statement += " >= ";
					} else if (*k == 2) {
						statement += " == ";
					} else if (*k == 3) {
						statement += " != ";
					}
				} else if (pos == 2) {
					++pos;
					statement += Standard::to_string<int>(*k) + "%";
				} else if (pos == 3) {
					pos = 0;
					if ((k != j->end()) && (next(k) == j->end())) {   // if last
						statement += ")";
					}

					if (*k == 1) {
						statement += " && ";
					} else if (*k == 2) {
						statement += " || ";
					}
				}
			}
		}
		statement += ")";
		std::cout << statement << endl;
	}

	std::cout << endl;
}

string Character::ReadStatement(vector<vector<int> > statement)
{
	string statement_return;
	int pos = 0;

	statement_return = "if (";

	for (auto j = statement.begin(); j != statement.end(); ++j) {
		statement_return += "(";
		for (auto k = j->begin(); k != j->end(); ++k) {
			if (pos == 0) {
				++pos;
				if (*k == 0) {
					statement_return += "health";
				} else if (*k == 1) {
					statement_return += "magic";
				} else if (*k == 2) {
					statement_return += "enemy.health";
				} else if (*k == 3) {
					statement_return += "enemy.magic";
				} else if (*k == 4) {
					statement_return += "true";
					pos = 3;
				}
			} else if (pos == 1) {
				++pos;
				if (*k == 0) {
					//statement_return += " &lt;= ";
					statement_return += " <= ";
				} else if (*k == 1) {
					//statement_return += " &gt;= ";
					statement_return += " >= ";
				} else if (*k == 2) {
					statement_return += " == ";
				} else if (*k == 3) {
					statement_return += " != ";
				}
			} else if (pos == 2) {
				++pos;
				statement_return += Standard::to_string(*k) + "%";
			} else if (pos == 3) {
				pos = 0;
				if ((k != j->end()) && (next(k) == j->end())) {   // if last
					statement_return += ")";
				}

				if (*k == 1) {
					statement_return += " AND ";
				} else if (*k == 2) {
					statement_return += " OR ";
				}
			}
		}
	}

	statement_return += ")";
	return statement_return;
}

string Character::ReadAbility(Game& game, int ability)
{
	if (ability == 0) {
		return "Normal Attack";
	} else {
		return game.abilities[abilities_[ability - 1] - 1]->name();
	}

	/*if (ability == 0) {
		return "Normal Attack";
	} else if (ability == 1) {
		return "Battle Cry";
	} else if (ability == 2) {
		return "Heal";
	} else if (ability == 3) {
		return "Hack";
	}*/

}

unsigned int Character::CountStuff()
{
	unsigned int count = 0;
	for (auto i = items_.begin(); i != items_.end(); ++i) {
		count += (i->moves.size());// -1) * 3;
		for (auto j = i->statement.begin(); j != i->statement.end(); ++j) {

			int pos = 0;
			for (auto k = j->begin(); k != j->end(); ++k) {
				if (pos == 0) {								// variables

					count += 2;

					if (*k == 4) {							// if a fallback
						pos = 3;
					} else {
						++pos;
					}
				} else if (pos == 1) {						// operators
					++pos;
				} else if (pos == 2) {						// percentages
					++pos;
				} else if (pos == 3) {						// gates/END
					pos = 0;
				}
			}
		}
	}

	return count;
}

bool Character::EvaluateStatement(vector<vector<int> > statement, Character& enemy)
{
	// NOTE: the order of operations is not implemented

	/*for (auto i = statement.begin(); i != statement.end(); ++i) {
		cout << "[";
		for (auto j = i->begin(); j != i->end(); ++j) {
			cout << *j << ", ";
		}
		cout << "]";
	}*/

	int first;
	int second;
	int pos = 0;

	vector<tuple<bool, int> > results;
	bool current_bool = true;
	bool temp_bool = true;
	int current_operator = 0;					// 0: none, 1: and, 2: or

	//cout << "BEGIN\n";
	for (auto j = statement.begin(); j != statement.end(); ++j) {
		current_bool = true;
		current_operator = 0;

		//cout << " L1\n";
		for (auto k = j->begin(); k != j->end();) {
			//cout << " L2\n";
			if (*k == 4) {						// if true/always
				//cout << " L2:0\n";
				if (current_operator == 1) {
					// current_bool = current_bool && true (doesn't change it)
				} else if (current_operator == 2) {
					// current_bool = current_bool || true (always true)
					current_bool = true;
				}

				++k;
				current_operator = *k;				// should only be 0 if this is the end of the last statement
				++k;
			} else {
				//cout << " L2:1\n";
				if (*k == 0) {
					first = health_;
					second = health_max_;
				} else if (*k == 1) {
					first = magic_;
					second = magic_max_;
				} else if (*k == 2) {
					first = enemy.health();
					second = enemy.health_max();
				} else if (*k == 3) {
					first = enemy.magic();
					second = enemy.magic_max();
				}

				//cout << "  L3-0\n";
				++k;
				//cout << "  L3-1\n";

				second = *next(k) * second * (1/100.);				// turns it from percentage to real
				//cout << "  L3-2\n";

				if (*k == 0) {										// <=
					temp_bool = (first <= second);
					//cout << first << " <= " << second << '\n';
				} else if (*k == 1) {								// >=
					temp_bool = (first >= second);
				} else if (*k == 2) {								// ==
					temp_bool = (first == second);
				} else if (*k == 3) {								// !=
					temp_bool = (first != second);
				}
				//cout << "  L3-5\n";
				
				//cout << "current_operator: " << current_operator << '\n';
				if (current_operator == 1) {							// and
					current_bool = (current_bool && temp_bool);
				} else if (current_operator == 2) {						// or
					current_bool = (current_bool || temp_bool);
				} else if (current_operator == 0) {						// nothing changes
					current_bool = temp_bool;
				}

				advance(k, 2);
				current_operator = *k;				// should only be 0 if this is the end of the last statement
				++k;
			}
		}

		results.push_back(tuple<bool, int>(current_bool, current_operator));
	}

	current_bool = get<0>(*results.begin());			// first statement's bool
	for (auto i = next(results.begin()); i != results.end(); ++i) {
		if (get<1>(*(i-1)) == 1) {			// and
			current_bool = (current_bool && get<0>(*i));
		} else if (get<1>(*(i-1)) == 2) {	// or
			current_bool = (current_bool || get<0>(*i));
		}
	}

	return current_bool;
}

void Character::Fight(Character& enemy, Game& game, bool show_text)
{
	if (health_ > 0) {
		auto highest_priority = items_.begin();
		for (auto i = items_.begin(); i != items_.end(); ++i) {
			//cout << EvaluateStatement(i->statement, enemy) << " ";
			if (i->specific > highest_priority->specific) {					// notice the > instead of >= (goes for first in list if equal)
				if (EvaluateStatement(i->statement, enemy)) {
					highest_priority = i;
				}
			}
		}




		if (current_item_ == highest_priority - items_.begin()) {
			// very complex, basically referenceing back a lot
			//int ref = *(abilities_.begin() + *(highest_priority->moves.begin() + current_item_move_)) - 1;
			//cout << "  A.1-0.0\n";
			//cout << current_item_move_ << '\n';
			int ref = *(highest_priority->moves.begin());
			//cout << "  A.1-0.1\n";
			ref = *(highest_priority->moves.begin() + current_item_move_);
			//cout << "  A.1-0.2\n";
			if (ref > 0) {
				ref = *(abilities_.begin() + (ref - 1));
			}
			
			//cout << "  A.1-0.5\n";
			Attack(ref, enemy, game, show_text);
			//cout << "  A.1-0.9\n";
			++current_item_move_;
			if (current_item_move_ >= highest_priority->moves.size()) {
				current_item_move_ = 0;
			}
			//cout << "  A.1-0.15\n";

		} else {
			current_item_ = highest_priority - items_.begin();
			current_item_move_ = 0;

			//*(highest_priority->moves.begin() + current_item_move_);
			int ref = *(highest_priority->moves.begin() + current_item_move_);
			if (ref > 0) {
				ref = *(abilities_.begin() + (ref - 1));
			}

			Attack(ref, enemy, game, show_text);

			++current_item_move_;
			if (current_item_move_ >= highest_priority->moves.size()) {
				current_item_move_ = 0;
			}
			//cout << "  A.1-1.5\n";

		}
	}
}

void Character::Attack(int ability_index, Character& enemy, Game& game, bool show_text)
{
	if (show_text)
		printf("(%d)\n", health_);
	if (ability_index != 0) {															// if not a regular attack
		int cost;
		if (game.abilities[ability_index - 1]->Use(*this, enemy, cost)) {				// if enough magic
			if (show_text)
				cout << game.abilities[ability_index - 1]->sentence();
			return;
		}																				// otherwise no return, continues to regular attack
	}

	if (show_text)
		printf("does a standard attack!");

	enemy.HealthDec(attack_);
}

void Character::UpdateBuffs(bool show_text, string name)
{
	for (auto i = buffs_.begin(); i != buffs_.end();) {
		if (health_ <= 0) {
			break;
		}

		if (show_text)
			if (!(*i)->dead())
				cout << "\n" << name << " " << (*i)->sentence();

		if ((*i)->Update(*this)) {		// if alive
			++i;
		} else {					// if dead
			i = buffs_.erase(i);
		}
	}
}

/*
void Character::AttackText(int ability_index, Character& enemy, Game& game)
{_
	printf("(%d)\n", health_);
	if (ability_index != 0) {															// if not a regular attack
		int cost;
		if (game.abilities[ability_index - 1]->Use(*this, enemy, cost)) {				// if enough magic
			cout << game.abilities[ability_index - 1]->sentence();
			return;
		}																				// otherwise no return, continues to regular attack
	}

	cout << "does a standard attack!";
	enemy.HealthDec(attack_);
}*/

/*void Character::UpdateBuffs()
{
	for (auto i = buffs_.begin(); i != buffs_.end();) {
		if (health_ <= 0) {
			break;
		}

#ifdef USING_COUT_
		if (!(*i)->dead())
			cout << (*i)->sentence();
#endif
		if ((*i)->Update(*this)) {		// if alive
			++i;
		} else {					// if dead
			i = buffs_.erase(i);
		}
	}
}*/

void Character::HealthInc(int amount)
{
	health_ += amount;
	if (health_ >= health_max_)
		health_ = health_max_;
}

void Character::HealthDec(int amount)
{
	health_ -= amount;
	if (health_ < 0)
		health_ = 0;
}

void Character::MagicDec(int amount)
{
	magic_ -= amount;
	if (magic_ < 0)
		magic_ = 0;
}

void Character::AttackInc(int amount)
{
	attack_ += amount;
	if (attack_ > attack_max_) {
		attack_ = attack_max_;
	}
}

void Character::BuffsAdd(shared_ptr<Buff> buff)
{
	int unique = buff->unique();
	if (unique == 0) {
		buffs_.push_back(move(buff));
	} else {
		string name = buff->name();
		int count = 0;

		auto least_turns_left = buffs_.begin();
		for (auto i = buffs_.begin(); i != buffs_.end(); ++i) {
			if ((*i)->name() == name) {
				if ((*i)->turns_left() < (*least_turns_left)->turns_left())
					least_turns_left = i;
				if (++count >= unique) {
					(*i)->Kill();
					buffs_.push_back(move(buff));
					break;
				}
			}
		}

		if (count < unique) {
			buffs_.push_back(move(buff));
		}
	}

}