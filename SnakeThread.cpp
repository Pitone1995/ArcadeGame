#include "SnakeThread.h"
#include "ConsoleUtils.h"
#include <iostream>

#define H_FIELD 25
#define W_FIELD 50

SnakeThread::SnakeThread() {
}

void SnakeThread::run() {

    /* TODO
    - check edges: change direction or enter from the other side?
    - spawn fruits in random position in the field
    - if eat fruit get bigger of 1
    - can use matrix of field dimension with 1 where fruits are
    - 0 when fruit is eaten
    - check if coordinates of head (m_x, m_y) match fruit -> eat
    - check if snake eats itself -> lose
    - when get bigger: draw head + previous position (2 positions, 2 positions)
    */

    while (1) {

        m_x = m_x + m_vx * m_xT;
        m_y = m_y + m_vy * m_yT;

        drawField();
    }
}

void SnakeThread::setXDirection(int v) {

    m_vx = v;
}

void SnakeThread::setYDirection(int v) {

    m_vy = v;
}

void SnakeThread::drawField() {

    Console::resetColor();
    system("cls");

    for (int i = 0; i < H_FIELD; i++) {

        for (int j = 0; j < W_FIELD; j++) {

            if (i == 0 || i == H_FIELD - 1)
                std::cout << "-";  
            else {

                if (j == 0 || j == W_FIELD - 1)
                    std::cout << "|";  
                else {

                    // Here i am in the field

                    // Color actual snake position
                    if (i == m_y && j == m_x)
                        Console::setColor(HIGHLIGHT_TXT);
                
                    std::cout << ' ';
                    Console::setColor(DEFAULT_TXT);

                }
            }

            if (j == W_FIELD - 1)
                std::cout << "" << std::endl;
        }
    }

    std::cout << "" << std::endl;
}