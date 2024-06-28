#include "SnakeThread.h"

#include "Utils.h"
#include <string>

#define H_FIELD 25
#define W_FIELD 50

#define FRUIT '@'
#define BODY ' '
#define H_EDGE '-'
#define V_EDGE '|'

SnakeThread::SnakeThread() {
    
    // Vector of field, obviously borders are excluded
    for (int y = 1; y < H_FIELD - 1; y++) {
        
        for (int x = 1; x < W_FIELD - 1; x++)
            m_field.push_back({x, y});
    }

    genBody();
    genFruit();
}

void SnakeThread::run() {

    /* TODO
    - check edges: change direction or enter from the other side?
    - check if snake eats itself -> lose
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

    for (int y = 0; y < H_FIELD; y++) {

        for (int x = 0; x < W_FIELD; x++) {

            if (y == 0 || y == H_FIELD - 1)
                Utils::drawElement(H_EDGE);
            else {

                if (x == 0 || x == W_FIELD - 1)
                    Utils::drawElement(V_EDGE);
                else {

                    // Here i am in the field

                    // Spawn or eat fruit
                    if (checkFruit(x, y)) {

                        // Spawn                   
                        if (!checkHead(x, y)) {
                        
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
                    else if (checkBody(x, y)) {      
            
                        if (checkHead(x, y))      
                            Utils::drawElement(BODY, GREEN_TXT);
                        else
                            Utils::drawElement(BODY, HIGHLIGHT_TXT);
                    }
                    else
                        Utils::drawElement(' ');
                }
            }
            if (x == W_FIELD - 1)
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