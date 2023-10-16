#include <iostream>
#include <vector>
#include <conio.h>

using namespace std;

vector<vector<char>> grid = { {'1', '2', '3'}
							, {'4', '5', '6'}
							, {'7', '8', '9'} }; //cells and their numbers

void drawGrid() { //this function draws the markup for tic-tac-toe
	int indexX, indexY = 0;

	for (int i = 0; i < 5; i++) {
		indexX = 0;

		if (i % 2 == 0) {
			cout << " " << grid[indexY][indexX++] << " | ";
			cout << grid[indexY][indexX++] << " | ";
			cout << grid[indexY++][indexX++] << endl;
		}
		else {
			cout << "---|---|---" << endl;
		}
	}
}

pair<int, int> buttonPressed(char player) {//this function allows player to select cell in console
	cout << "Please select the cell where you want to insert " << player << endl;

	char key;
	int indexX, indexY;

	while (true) {
		if (_kbhit()) {
			key = _getch();
			if (key >= '1' && key <= '9') {

				indexX = ((key - '0') - 1) % 3;
				indexY = ((key - '0') - 1) / 3;

				if (grid[indexY][indexX] != 'X' && grid[indexY][indexX] != 'O') {//checks if the cell is already occupied
					grid[indexY][indexX] = player;
					return make_pair(indexX, indexY);
				}
			}
		}
	}
}

bool checkWinner(pair<int, int> position) {
	int row = position.second;
	int col = position.first;
	char player = grid[row][col];

	// checking the winner horizontally
	bool winInHorizont = true;
	for (int j = 0; j < 3; j++) {
		if (grid[row][j] != player) {
			winInHorizont = false;
			break;
		}
	}

	// checking the winner vertically
	bool winInVertical = true;
	for (int i = 0; i < 3; i++) {
		if (grid[i][col] != player) {
			winInVertical = false;
			break;
		}
	}

	// checking the winner along the main diagonal, if the cell is on it
	bool winInMainDiagonal = false;
	if (row == col) {
		winInMainDiagonal = true;
		for (int i = 0; i < 3; i++) {
			if (grid[i][i] != player) {
				winInMainDiagonal = false;
				break;
			}
		}
	}

	// checking the winner on the anti-diagonal, if the cell is on it
	bool winInAntiDiagonal = false;
	if (row + col == 2) {
		winInAntiDiagonal = true;
		for (int i = 0; i < 3; i++) {
			if (grid[i][2 - i] != player) {
				winInAntiDiagonal = false;
				break;
			}
		}
	}

	return winInHorizont || winInVertical || winInMainDiagonal || winInAntiDiagonal;
}


int main() {
	char winner = ' ';
	char currentPlayer = 'X', key;
	bool continuePlaying = true;

	while (continuePlaying) {
		for (int move = 0; move < 9; move++) {
			system("cls"); // clearing console

			cout << "Press keys 1-9 of your keyboard to select a cell." << endl;

			drawGrid();

			pair<int, int> position = buttonPressed(currentPlayer);

			if (checkWinner(position)) {
				winner = currentPlayer;
				break;
			}

			currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
		}

		system("cls");
		drawGrid();

		if (winner != ' ') {
			cout << "Player " << winner << " won!" << endl;
		}
		else {
			cout << "Draw!" << endl;
		}

		cout << "Do you want to play again? (Y/N): ";

		while (true) {
			if (_kbhit()) {
				key = _getch();
				if (key == 'n') {
					continuePlaying = false;
					break;
				}
				else if (key == 'y') {
					grid = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} }; // default settings for a new game
					winner = ' ';
					currentPlayer = 'X';
					break;
				}
			}
		}
	}

	return 0;
}