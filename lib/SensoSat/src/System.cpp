#include "System.h"

void System::initI2CBuses()
{
    // Wire.setSCL(WIRE_SCL_PIN);
    // Wire.setSDA(WIRE_SDA_PIN);
    // Wire.begin();


    // Wire1.setSCL(WIRE1_SCL_PIN);
    // Wire1.setSDA(WIRE1_SDA_PIN);
    // Wire1.begin();
}

System::System()
{
}

void System::init()
{
    Serial.begin(9600);
    initI2CBuses();
}
