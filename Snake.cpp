#include "Snake.h"

#include "SnakeThread.h"

#include "ConsoleUtils.h"
#include <iostream>
#include <conio.h>

using namespace std;

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

            st.setYDirection(V_NEG);
            st.setXDirection(V_NUL);
            break;

        case DWN_ARROW:

            st.setYDirection(V_POS);
            st.setXDirection(V_NUL);
            break;

        case LEFT_ARROW:

            st.setXDirection(V_NEG);
            st.setYDirection(V_NUL);
            break;

        case RIGHT_ARROW:

            st.setXDirection(V_POS);
            st.setYDirection(V_NUL);
            break;

        default:
            break;
        }
    }
}