#ifndef DELTA_TIME_H
#define DELTA_TIME_H

#include <time.h>

class DeltaTime{
private:
    long milliseconds_now() {
        timespec now;
        int err = clock_gettime(CLOCK_MONOTONIC, &now);
        return now.tv_sec * 1000.0L + now.tv_nsec / 1000000.0L;
    }
    long timeCounter;
    float deltaTime;
public:
    static DeltaTime* getDeltaTimeClass();
    
    void init();
    const float getDeltaTime();
    long getTimeSinceLastUpdate();
    void update();
};

#endif
