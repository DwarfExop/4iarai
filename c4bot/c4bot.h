// c4bot.h
// Aswin van Woudenberg

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

	std::vector<std::vector<Move>> winRoute = {
		{ 3,3,3,3,3,3,2,1,5,4,4,2 }
	};

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

	// ---
	std::array<int, 2> miniMax(int ply, const State &board, const Player &player, int alpha, int beta);
	int eval(const State &board, const Player &player, const int &ply);
	int getTimeElapsed();
	Move checkState();

public:
	void run();
};

#endif // C4BOT_H

