#include <iostream>
#include <vector>

#include "Menu.h"
#include "TicTacToe.h"
#include "Snake.h"

using namespace std;

enum {

	TICTACTOE,
	SNAKE,
	QUIT
};

int main(int argc, char *argv[]) {

	vector<string> options = {"Tic-Tac-Toe", "Snake", "Quit"};
	// vector<string> options = {"New game", "Load game", "Quit"};
	Menu mainMenu(options);

	while (1) {
		
		int selIndex = mainMenu.run();
		switch (selIndex) {

			case TICTACTOE: {
				TicTacToe game;
				game.run();
			}
				break;

			case SNAKE: {
				Snake snake;
				snake.run();
				// mainMenu.clear();
				// cout << "Load game selected: press any key to return to main menu...";
				// system("pause > nul");
			}
				break;

			default: // QUIT
				return 0;
				break;
		}
	}

	return 0;
}
