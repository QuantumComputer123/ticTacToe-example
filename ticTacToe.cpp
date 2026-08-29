#include <array>
#include <iostream>
#include <string>

using std::array, std::string;

struct Board {
	array<array<int, 3>, 3> state = {};

	char numToChar(int num) {
		switch (num) {
			case 0:
				return ' ';
			case 1:
				return 'X';
			case 2:
				return 'O';
			default:
				return 'E';
		}
	}

	void print() {
		std::cout << "   a   b   c\n +---+---+---+\n1| " << numToChar(state[0][0]) << " | "
				  << numToChar(state[0][1]) << " | " << numToChar(state[0][2]) << " |\n +---+---+---+\n"
																				  "2| "
				  << numToChar(state[1][0]) << " | " << numToChar(state[1][1]) << " | " << numToChar(state[1][2]) << " |\n +---+---+---+\n3| " << numToChar(state[2][0]) << " | " << numToChar(state[2][1]) << " | " << numToChar(state[2][2]) << " |\n +---+---+---+" << std::endl;
	}
};

int numFromIndex(const string& index) {
	int num = 0;
	if (index[0] == 'b') num += 1;
	if (index[0] == 'c') num += 2;

	if (index[1] == '2') num += 3;
	if (index[1] == '3') num += 6;

	if (index.size() > 2) {
		return 0;
	}

	return num;
};

bool gameWon(const Board& board) {
	for (int player = 1; player <= 2; ++player) {
		for (int i = 0; i < 3; i++) {
			if (board.state[i][0] == player && board.state[i][1] == player && board.state[i][2] == player) {
				return true;
			}
		}

		for (int i = 0; i < 3; i++) {
			if (board.state[0][i] == player && board.state[1][i] == player && board.state[2][i] == player) {
				return true;
			}
		}

		if (board.state[0][0] == player && board.state[1][1] == player && board.state[2][2] == player) {
			return true;
		}
		if (board.state[0][2] == player && board.state[1][1] == player && board.state[2][0] == player) {
			return true;
		}
	}

	return false;
}

int main() {
	Board board;

	bool player = false;

	bool retry = false;

	int turn = 1;

	std::cout << "Player 1's turn. Type a letter (a-c), then a number (1-3)!\n";

	while (!gameWon(board) && turn < 10) {
		std::cout << "Turn: " << turn << '\n';
		retry = false;

		string input;
		std::cin >> input;

		if (input == "q") return 0;

		if (board.state.at((int)(numFromIndex(input) / 3)).at(numFromIndex(input) % 3) == 0) {
			board.state.at((int)(numFromIndex(input) / 3)).at(numFromIndex(input) % 3) = (int)player + 1;
		} else {
			retry = true;
		}

		if (!retry) {
			player = !player;

			board.print();
			turn++;
		} else {
			std::cout << "Retry (square already taken or invalid)\n";
		}
	}

	if (gameWon(board)) {
		std::cout << "Player " << (int)!player + 1 << " won the game!\n";
	} else {
		std::cout << "It's a draw!\n";
	}

	return 0;
}