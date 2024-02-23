#ifndef SYSTEM_H
#define SYSTEM_H
#include "Arduino.h"

#include "Config.h"

#include <Wire.h>

class System
{
private:
    void initI2CBuses();
    /* data */
public:
    System();
    void init();
};



#endif