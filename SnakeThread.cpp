#include "SnakeThread.h"
#include "ConsoleUtils.h"
#include <iostream>

#include <string>

#define H_FIELD 25
#define W_FIELD 50

SnakeThread::SnakeThread() {
    
    std::pair<int, int> initialCoord(m_x, m_x);
    m_body.push_back(initialCoord);
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
    - when get bigger: draw head + previous position (2 positions, 3 positions)
    */

    while (1) {

        updateBodyCoord();
        checkEdges();
        drawField();
    }
}

void SnakeThread::setXDirection(V vel) {

    m_vx = vel;
}

void SnakeThread::setYDirection(V vel) {

    m_vy = vel;
}

void SnakeThread::drawField() {

    //Console::resetColor();
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

                    // Spawn fruit
                    if (checkFruit(j, i) && !checkHead(j, i)) {
                        
                        if (m_fruit)
                            std::cout << 'O';
                        else {

                            std::cout << ' ';

                            // Generate new fruit coordinates and spawn at next iteration
                            m_fruit = true;
                            // m_xFruit++;
                            // m_yFruit++;
                        }
                    }
                    // Color actual snake positions
                    else if (!checkFruit(j, i) && checkBody(j, i)) {      
            
                        Console::setColor(HIGHLIGHT_TXT);
                        std::cout << ' ';
                        Console::setColor(DEFAULT_TXT);
                    }
                    else {

                        // Eat
                        if (checkFruit(j, i) && checkHead(j, i)) {
                            
                            m_fruit = false;
                            m_countFruit++;
                            m_xFruit++;
                            m_yFruit++;
                            Console::setColor(HIGHLIGHT_TXT);
                        }

                        std::cout << ' ';
                        Console::setColor(DEFAULT_TXT);
                    }
                }
            }

            if (j == W_FIELD - 1)
                std::cout << "" << std::endl;
        }
    }

    std::cout << "" << std::endl;
}

void SnakeThread::checkEdges() {

    if (m_x < 1)
        m_x = W_FIELD - 1;
    else if (m_x > W_FIELD - 2)
        m_x = 0;

    if (m_y < 1)
        m_y = H_FIELD - 1;
    else if (m_y > H_FIELD - 2)
        m_y = 0;

    // std::string a = "m_x = " + std::to_string(m_x) + " m_y = " + std::to_string(m_y);
    // std::string b = "echo '" + a + "' >> log.txt";
    // system(b.c_str());
}

bool SnakeThread::checkHead(int x, int y) {
    return (x == m_x && y == m_y);
}

bool SnakeThread::checkFruit(int x, int y) {
    return (x == m_xFruit && y == m_yFruit);
}

bool SnakeThread::checkBody(int x, int y) {

    std::pair<int, int> actualCoord(x, y);
    if (std::find(m_body.begin(), m_body.end(), actualCoord) != m_body.end())
        return true;
    else
        return false;
}

void SnakeThread::updateBodyCoord() {

    m_x = m_x + m_vx * m_xT;
    m_y = m_y + m_vy * m_yT;

    std::pair<int, int> actualCoord(m_x, m_y);
    m_body.push_back(actualCoord);

    // I want to keep m_countFruit + 1 coordinates
    while (m_body.size() > (m_countFruit + 1))
        m_body.erase(m_body.begin());
}