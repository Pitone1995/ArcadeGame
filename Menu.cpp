#include "Menu.h"

#include "Utils.h"
#include <conio.h>

using namespace std;

Menu::Menu(vector<string> &options) :
m_options{options} {
	
	Utils::ShowConsoleCursor(false);
}

Menu::~Menu() {

	clear();
	Utils::ShowConsoleCursor(true);
}

/* This function returns when ENTER is pressed */
int Menu::run() {

	int key = 0;

	while (key != ENTER) {

		clear();
		showOpt();

		key = _getch();

		/* getch () function returns two keycodes for arrow keys. Arrow put to getch '\033' and '[' and letter from A to D (up, down, right, left).
		Check if the first value is escape and skip */
		if (key == 224)
			key = _getch();

		switch (key) {

		case UP_ARROW:
			m_selIndex--;
			if (m_selIndex == -1)
				m_selIndex = 2;
			break;

		case DWN_ARROW:
			m_selIndex++;
			if (m_selIndex == 3)
				m_selIndex = 0;
			break;

		default:
			break;
		}		
	}

	return m_selIndex;
}

void Menu::showOpt() {

	for (int i = 0; i < m_options.size(); i++) {

		if (i == m_selIndex)
			Utils::setColor(HIGHLIGHT_TXT);
		else
			Utils::setColor(DEFAULT_TXT);

		cout << m_options.at(i) << endl;
	}
}

void Menu::clear() {

	Utils::resetColor();
	system("cls");
}
