#ifndef Snake_H
#define Snake_H

#define H_FIELD 25
#define W_FIELD 50

class Snake {

public:

    Snake();
    void run();

private:

    void drawField();
    void moveSnake();

    bool m_play = true;
    int m_field[H_FIELD][W_FIELD];
    int m_currRow = 10;
    int m_currCol = 10;
};

#endif