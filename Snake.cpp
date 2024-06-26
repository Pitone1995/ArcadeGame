#include "Snake.h"

#include "SnakeThread.h"

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
}

void Snake::run() {

    SnakeThread st;
    st.StartInternalThread();

    while (m_play) {

        int key = _getch();

        /* getch () function returns two keycodes for arrow keys. Arrow put to getch '\033' and '[' and letter from A to D (up, down, right, left).
        Check if the first value is escape and skip */
        if (key == 224)
            key = _getch();

        switch (key) {

        case UP_ARROW:

            st.setYDirection(-1);
            st.setXDirection(0);
            break;

        case DWN_ARROW:

            st.setYDirection(1);
            st.setXDirection(0);
            break;

        case LEFT_ARROW:

            st.setXDirection(-1);
            st.setYDirection(0);
            break;

        case RIGHT_ARROW:

            st.setXDirection(1);
            st.setYDirection(0);
            break;

        default:
            break;
        }
    }
}