#ifndef Utils_H
#define Utils_H

#include <windows.h>
#include <string>
#include <iostream>
#include <random>

// From color --help
#define HIGHLIGHT_TXT 0xF0
#define DEFAULT_TXT 0x7
#define GREEN_TXT 32
#define RED 12
#define GREEN 0xA

#define UP_ARROW 72
#define DWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define ENTER 13

class Utils {

public:

    static void setColor(unsigned short int code) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, code);
	}

	static void resetColor() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, DEFAULT_TXT);
	}

	static void ShowConsoleCursor(bool showFlag)
	{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_CURSOR_INFO cursorInfo;

		GetConsoleCursorInfo(out, &cursorInfo);
		cursorInfo.bVisible = showFlag; // set the cursor visibility
		SetConsoleCursorInfo(out, &cursorInfo);
	}

    static void clearScreen() {
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		COORD coord = { 0, 0 };
		DWORD count;

		if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
		{
			DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;

			// Ripristina il testo e il colore di sfondo predefiniti
			WORD defaultAttributes = csbi.wAttributes;
			FillConsoleOutputAttribute(hStdOut, defaultAttributes, consoleSize, coord, &count);

			// Pulisce lo screen buffer con spazi bianchi
			FillConsoleOutputCharacter(hStdOut, ' ', consoleSize, coord, &count);

			// Riposiziona il cursore nella posizione iniziale
			SetConsoleCursorPosition(hStdOut, coord);
		}
	}

    static int genRandomInt(int min, int max) {

            std::random_device rd; // obtain a random number from hardware
            std::mt19937 gen(rd()); // seed the generator
            std::uniform_int_distribution<> distr(min, max); // define the range

        return distr(gen); // generate number
    }

    static void drawElement(char element) {
    	std::cout << element;
	}

	static void drawElement(char element, int color) {

		setColor(color);
    	std::cout << element;
    	setColor(DEFAULT_TXT);
	}
};

#endif
