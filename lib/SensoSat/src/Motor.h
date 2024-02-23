#ifndef MOTOR_H
#define MOTOR_H
#include "Arduino.h"
#include "Servo.h"

#include "Config.h"

#include <Wire.h>

enum Diretion {
    RIGHT,
    LEFT
};

class Motor
{
private:
    unsigned int nextUpdate = 0;
    int targetPWM = 1500;
    int currentPWM = 1500;

public:
    void init();
    void setTarget(int);
    void update();

};



#endif