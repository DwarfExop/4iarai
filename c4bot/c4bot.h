// c4bot.h
// Aswin van Woudenberg
// Lars Schipper (DwarfExop)

#ifndef C4BOT_H
#define C4BOT_H

#include <string>
#include <vector>
#include <chrono>

#include "c4.h"

class C4Bot {
	int timebank;
	int time_per_move;
	std::string player_names[2];
	std::string your_bot;
	int your_botid;
	int field_columns;
	int field_rows;
	Player bot = Player::X;
	Player opp = Player::O;

	int round;
	State state = { { { { Player::None } } } };

	clock_t start;
	int time;

	// possible good routes to follow
	std::vector<std::vector<Move>> winRoute = {
		{ 3,3,3,3,3,4,4,4,4,4,6,6,6,1,1 },
		{ 3,3,3,3,3,4,4,4,4,1,4,2,5,6,5,5,5 },
		{ 3,3,3,3,3,2,5,2 },
		{ 3,3,2,2,4,1,5 },
		{ 3,3,2,2,4,5,1 },
		{ 3,3,4,4,2,1 },
		{ 3,3,2,3,4 },
		{ 3,3,4,3,2 },
		{ 3,3,2,4,4,3,4 },
		{ 3,3,3,3,3,5,5,5,5,3,2,1 },
		{ 3,3,3,3,3,0,2,1,1,1,5,4 },
		{ 3,3,3,3,3,3,4,5,1,2,2,2 },
		{ 3,3,3,3,3,5,5,5,5,1,1,1 },
		{ 3,3,3,3,3,0,4,5,5,5,5,1 },
		{ 3,3,3,3,3,2,2,2,2,5,2,0 },
		{ 3,3,3,3,3,4,4,4,4,1,4,1 },
		{ 3,3,3,3,3,6,2,1,1,1,1,5 },
		{ 3,3,3,3,3,4,1,0,1,1,1,0 },
		{ 3,3,2,4,3,4,3,3,1,0,2 }
	};

	// evaluation table
	std::vector<std::vector<int>> evaluationTable = {
		{ 3, 4, 5, 7, 5, 4, 3 },
		{ 4, 6, 8, 10, 8, 6, 4 },
		{ 5, 8, 11, 13, 11, 8, 5 },
		{ 5, 8, 11, 13, 11, 8, 5 },
		{ 4, 6, 8, 10, 8, 6, 4 },
		{ 3, 4, 5, 7, 5, 4, 3 }
	};

	std::vector<std::string> split(const std::string &s, char delim);
	void setting(std::string &key, std::string &value);
	void update(std::string &key, std::string &value);
	void move(int timeout);

	std::array<int, 2> miniMax(int ply, const State &board, const Player &player, int alpha, int beta);
	int eval(const State &board, const Player &player, const int &ply);
	int getTimeElapsed();
	Move checkState();

public:
	void run();
};

#endif // C4BOT_H

