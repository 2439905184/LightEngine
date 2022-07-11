#include "DeltaTime.h"

DeltaTime* DeltaTime::getDeltaTimeClass(){
    static DeltaTime *instance;

    if (instance == 0){
        instance = new DeltaTime();
    }

    return instance;
}


void DeltaTime::init(){
    timeCounter = milliseconds_now();
}

void DeltaTime::update(){
    deltaTime = (float)getTimeSinceLastUpdate() / 1000.0f;      // update delta time
    timeCounter = milliseconds_now();                           // set time counter to current time
}

long DeltaTime::getTimeSinceLastUpdate(){
    return milliseconds_now() - timeCounter;                    // current time - time for previous update
}

float const DeltaTime::getDeltaTime(){
    return deltaTime;
}

