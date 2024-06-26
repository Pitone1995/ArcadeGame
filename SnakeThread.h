#ifndef SnakeThread_H
#define SnakeThread_H

#include <pthread.h>

class SnakeThread {

public:

    SnakeThread();
    
    /** Returns true if the thread was successfully started, false if there was an error starting the thread */
    bool StartInternalThread() {
        return (pthread_create(&_thread, NULL, InternalThreadEntryFunc, this) == 0);
    }

    void drawField();

    // User intervention
    void setXDirection(int v);
    void setYDirection(int v);

private:

    void run();

    int m_x = 1;
    int m_y = 1;
    int m_xT = 1;
    int m_yT = 1;
    int m_vx = 1;
    int m_vy = 0;

    static void *InternalThreadEntryFunc(void *This) {((SnakeThread *)This)->run(); return NULL;}
    pthread_t _thread;
};

#endif