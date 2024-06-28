#include "SnakeThread.h"

#include "Utils.h"
#include <string>

#define H_FIELD 25
#define W_FIELD 50

#define FRUIT '@'
#define BODY ' '

SnakeThread::SnakeThread() {
    
    // Vector of field, obviously borders are excluded
    for (int i = 1; i < H_FIELD - 1; i++) {
        for (int j = 1; j < W_FIELD - 1; j++)
            m_field.push_back({j, i});
    }

    genBody();
    genFruit();
}

void SnakeThread::run() {

    /* TODO
    - check edges: change direction or enter from the other side?
    - spawn fruits in random position in the field
    - if eat fruit get bigger of 1
    - check if coordinates of head (m_x, m_y) match fruit -> eat
    - check if snake eats itself -> lose
    - when get bigger: draw head + previous position (2 positions, 3 positions)
    */

    while (1) {

        genFruit();
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

    system("cls");

    for (int i = 0; i < H_FIELD; i++) {

        for (int j = 0; j < W_FIELD; j++) {

            if (i == 0 || i == H_FIELD - 1)
                Utils::drawElement('-');
            else {

                if (j == 0 || j == W_FIELD - 1)
                    Utils::drawElement('|');
                else {

                    // Here i am in the field

                    // Spawn or eat fruit
                    if (checkFruit(j, i)) {

                        // Spawn                   
                        if (!checkHead(j, i)) {
                        
                            if (m_fruit)
                                Utils::drawElement(FRUIT, RED);
                            else
                                Utils::drawElement(' ');
                        }
                        // Eat
                        else {

                            // Generate new fruit coordinates and spawn at next iteration
                            m_fruit = false;
                            m_countFruit++;

                            // Draw head
                            Utils::drawElement(BODY, GREEN_TXT);
                        }

                    }
                    // Color actual snake positions
                    else if (checkBody(j, i)) {      
            
                        if (checkHead(j, i))      
                            Utils::drawElement(BODY, GREEN_TXT);
                        else
                            Utils::drawElement(BODY, HIGHLIGHT_TXT);
                    }
                    else
                        Utils::drawElement(' ');
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

void SnakeThread::genBody() {
    
    int randomIndex = Utils::genRandomInt(0, m_field.size() - 1);
    m_x = m_field.at(randomIndex).first;
    m_y = m_field.at(randomIndex).second;

    m_body.push_back(std::pair<int, int>{m_x, m_y});
}

void SnakeThread::genFruit() {

    if (!m_fruit) {
    
        // Need to do m_field - m_body and pick a random pair from the result
        std::sort(m_field.begin(), m_field.end());

        // i do not want the m_body to be sorted
        std::vector<std::pair<int, int>> m_bodyCopy = m_body;
        std::sort(m_bodyCopy.begin(), m_bodyCopy.end());

        std::vector<std::pair<int, int>> availableFruitPos;
        std::set_difference(
            m_field.begin(), m_field.end(), m_bodyCopy.begin(), m_bodyCopy.end(),
            std::back_inserter( availableFruitPos )
            );

        int randomIndex = Utils::genRandomInt(0, availableFruitPos.size() - 1);
        m_xFruit = availableFruitPos.at(randomIndex).first;
        m_yFruit = availableFruitPos.at(randomIndex).second;

        m_fruit = true;
    }
}