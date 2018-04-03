// c4bot.cpp
// Aswin van Woudenberg

#include "c4bot.h"

#include <iostream>
#include <sstream>

void C4Bot::run() {
	std::string line;
	while (std::getline(std::cin, line)) {
		std::vector<std::string> command = split(line, ' ');
		if (command[0] == "settings") {
			setting(command[1], command[2]);
		}
		else if (command[0] == "update" && command[1] == "game") {
			update(command[2], command[3]);
		}
		else if (command[0] == "action" && command[1] == "move") {
			move(std::stoi(command[2]));
		}
		else {
			std::cerr << "Unknown command: " << line << std::endl;
		}
	}
}

int C4Bot::getTimeElapsed() {
	clock_t now = clock();
	return (now - start) / (CLOCKS_PER_SEC / 1000);
}

int C4Bot::eval(const State &board, const Player &player, const int &ply)
{
	if (getWinner(board) == bot) return  10000000;
	if (getWinner(board) == opp) return -10000000;


	int utility = 138;
	int sum = 0;
	for (int i = 0; i < 6; i++)
		for (int j = 0; j <7; j++)
			if (board[i][j] == bot)
				sum += evaluationTable[i][j];
			else if (board[i][j] == opp)
				sum -= evaluationTable[i][j];
	return utility + sum + ply;
}

std::array<int, 2> C4Bot::miniMax(int ply, const State &board, const Player &player, int alpha, int beta)
{
	std::vector<Move> nextMoves = getMoves(board);

	int bestScore;
	Move bestMove = 0;

	if (nextMoves.empty() || ply == 0 || getTimeElapsed() + 500 > time) {
		bestScore = eval(board, player, ply);
		return { bestScore, bestMove };
	}
	else {
		for (int i = 0; i < nextMoves.size(); i++) {
			// Try a move
			State newBoard = doMove(board, nextMoves[i]);
			if (player == bot) { // Computer
				bestScore = miniMax(ply - 1, newBoard, opp, alpha, beta)[0];
				if (bestScore > alpha) {
					alpha = bestScore;
					bestMove = nextMoves[i];
				}
			}
			else { // Player
				bestScore = miniMax(ply - 1, newBoard, bot, alpha, beta)[0];
				if (bestScore < beta) {
					beta = bestScore;
					bestMove = nextMoves[i];
				}
			}

			// Tree cut-off
			if (alpha >= beta) break;
		}
		return { (player == bot) ? alpha : beta, bestMove };
	}

}

Move C4Bot::checkState() 
{
	for (auto win : winRoute) {
		State temp = { { { { Player::None } } } };

		for (int i = 0; i < win.size() -1; i++) {
			temp = doMove(temp, win[i]);
			if (temp == state && i % 2 == 0 && bot == Player::O) return win[i + 1];
			else if (temp == state && i % 2 != 0 && bot == Player::X) return win[i + 1];
		}
	}

	return -1;
}

void C4Bot::move(int timeout)
{
	time = timeout;
	start = clock();

	int alpha = std::numeric_limits<int>::min();
	int beta = std::numeric_limits<int>::max();

	Move bestMove = checkState();

	bestMove == -1 ? std::cerr << "used ab" : std::cerr << "used route";

	if(bestMove == -1) bestMove = miniMax(8, state, getCurrentPlayer(state), alpha, beta)[1];

	std::cout << "place_disc " << bestMove << std::endl;

	std::cerr << "Elapsed time: " << getTimeElapsed() << " in round: " << round << std::endl;

}

void C4Bot::update(std::string &key, std::string &value) {
	if (key == "round") {
		round = std::stoi(value);
	}
	else if (key == "field") {
		int row = 0;
		int col = 0;
		std::vector<std::string> fields = split(value, ',');
		for (std::string &field : fields) {
			if (field == "0") {
				state[row][col] = Player::X;
			}
			else if (field == "1") {
				state[row][col] = Player::O;
			}
			else {
				state[row][col] = Player::None;
			}
			col++;
			if (col == 7) {
				row++;
				col = 0;
			}
		}
	}
}

void C4Bot::setting(std::string &key, std::string &value) {
	if (key == "timebank") {
		timebank = std::stoi(value);
	}
	else if (key == "time_per_move") {
		time_per_move = std::stoi(value);
	}
	else if (key == "player_names") {
		std::vector<std::string> names = split(value, ',');
		player_names[0] = names[0];
		player_names[1] = names[1];
	}
	else if (key == "your_bot") {
		your_bot = value;
		if (your_bot == "player1") {
			bot = Player::O;
			opp = Player::X;
		}
	}
	else if (key == "your_botid") {
		your_botid = std::stoi(value);
	}
	else if (key == "field_columns") {
		field_columns = std::stoi(value);
	}
	else if (key == "field_rows") {
		field_rows = std::stoi(value);
	}
}

std::vector<std::string> C4Bot::split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

