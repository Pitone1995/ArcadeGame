#ifndef SnakeThread_H
#define SnakeThread_H

#include <algorithm>
#include <utility>
#include <vector>

#include <pthread.h>

typedef enum {

    V_NEG = -1,
    V_NUL,
    V_POS
} V;

class SnakeThread {

public:

    SnakeThread();

    // Courtesy of https://stackoverflow.com/questions/1151582/pthread-function-from-a-class

    /** Returns true if the thread was successfully started, false if there was an error starting the thread */
    bool StartInternalThread() {
        return (pthread_create(&_thread, NULL, InternalThreadEntryFunc, this) == 0);
    }

    // User intervention
    void setXDirection(V vel);
    void setYDirection(V vel);

private:

    void run();
    void drawField();
    void checkEdges();
    bool checkFruit(int x, int y);
    bool checkHead(int x, int y);
    bool checkBody(int x, int y);
    void genFruit();
    void updateBodyCoord();

    static void *InternalThreadEntryFunc(void *This) {((SnakeThread *)This)->run(); return NULL;}
    pthread_t _thread;

    // Law of motion's components
    int m_x = 1;
    int m_y = 1;
    int m_xT = 1;
    int m_yT = 1;
    V m_vx = V_POS;
    V m_vy = V_NUL;

    bool m_fruit = false;
    int m_xFruit = 1;
    int m_yFruit = 1;
    int m_countFruit = 0;

    // Snake's body
    std::vector<std::pair<int, int>> m_body;

    std::vector<std::pair<int, int>> m_field;
};

#endif