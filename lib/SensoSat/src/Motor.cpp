#include "Motor.h"

Servo MotorServo;

void Motor::init()
{
    MotorServo.attach(27);
    nextUpdate = 0;
    MotorServo.writeMicroseconds(1500);
    delay(3000);
}

void Motor::setTarget(int newTarget)
{
    targetPWM = newTarget;
}

void Motor::update()
{
    // Serial.println("AA");

    if (nextUpdate < millis())
    {
        // Serial.println("BB");

        if (targetPWM == currentPWM)
        {
        // Serial.println("CC");
            return;
        }

        if (targetPWM < currentPWM)
        {
            // Serial.println("DD");
            currentPWM -= 5;
        }
        else
        {
            // Serial.println("EE");
            currentPWM += 5;
        }

        Serial.println(currentPWM);


        MotorServo.writeMicroseconds(currentPWM);

        nextUpdate = millis() + 400;
    }
}
