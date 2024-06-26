#include "Snake.h"

#include "ConsoleUtils.h"
#include <iostream>
#include <conio.h>

using namespace std;

#define UP_ARROW 72
#define DWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define ENTER 13

Snake::Snake() {

     for (int i = 0; i < H_FIELD; i++) {
      
        for (int j = 0; j < W_FIELD; j++)
            m_field[i][j] = 0;
     } 

     m_field[m_currRow][m_currCol] = 1;
}

void Snake::run() {

    Console::resetColor();
	system("cls");
    drawField();

    while (m_play) {

        moveSnake();
        drawField();
    }
}

void Snake::drawField() {

    Console::resetColor();
    system("cls");

    for (int i = 0; i < H_FIELD; i++) {

        for (int j = 0; j < W_FIELD; j++) {

            if (i == 0 || i == H_FIELD - 1)
                cout << "-";  
            else {

                if (j == 0 || j == W_FIELD - 1)
                    cout << "|";  
                else {
                    // mi trovo nell'area in cui si può muovere il serpente

                    if (m_field[i][j])
                        Console::setColor(HIGHLIGHT_TXT);
                
                    cout << ' ';
                    Console::setColor(DEFAULT_TXT);

                }
            }

            if (j == W_FIELD - 1)
                cout << "" << endl;
        }
    }

    cout << "" << endl;
    cout << "r = " << m_currRow << " c = " << m_currCol << endl;
}

void Snake::moveSnake() {

    int key = _getch();

    /* getch () function returns two keycodes for arrow keys. Arrow put to getch '\033' and '[' and letter from A to D (up, down, right, left).
    Check if the first value is escape and skip */
    if (key == 224)
        key = _getch();

    switch (key) {

    case UP_ARROW:

        if (m_currRow > 1) {
            
            m_currRow--;
            m_field[m_currRow][m_currCol] = 1;
        }
        break;

    case DWN_ARROW:

        if (m_currRow < H_FIELD - 2) {
        
            m_currRow++;
            m_field[m_currRow][m_currCol] = 1;
        }
        break;

    case LEFT_ARROW:

        if (m_currCol > 1) {

            m_currCol--;
            m_field[m_currRow][m_currCol] = 1;
        }
        break;

    case RIGHT_ARROW:

        if (m_currCol < W_FIELD - 2) {

            m_currCol++;
            m_field[m_currRow][m_currCol] = 1;
        }
        break;

    default:
        break;
    }
}