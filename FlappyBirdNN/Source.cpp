#include <SFML/Graphics.hpp>
#include "Game.h"
#include "UserGame.h"
#include "AiGame.h"

int main() {
	int choice;
	cout << "Choose Game Mode" << endl;
	cout << "1) User Game" << endl;
	cout << "2) Ai Game" << endl;
	cin >> choice;
	if (choice == 1) {
		Game* game = new UserGame();
		game->Start();
	}
	else {
		string loadFile, saveFile;
		cout << "--------------" << endl;
		cout << "-   Ai Game  -" << endl;
		cout << "--------------" << endl;
		cout << "Choose load file and save file or input 0 for none" << endl;
		cin >> loadFile;
		cin >> saveFile;
		Game* game = new AiGame(loadFile, saveFile);
		game->Start();
	}

}