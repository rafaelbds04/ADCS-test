#include "Arduino.h"
#include "System.h"
#include "Sensors.h"
#include "Motor.h"

#include <math.h>
#include <PID_v1.h>

System sys;
Sensors sensors;
Motor motor;

double Pk1 = 10;
double Ik1 = 5;
double Dk1 = 0.01;
unsigned long fm = 0;

double Setpoint1, Input1, Output1; // PID variables
PID PID1(&Input1, &Output1, &Setpoint1, Pk1, Ik1, Dk1, DIRECT);

void setup()
{
  sys.init();
  sensors.initAllSensors();
  motor.init();
  // motor.setTarget(1700);

  PID1.SetMode(AUTOMATIC);
  PID1.SetOutputLimits(1000, 2000);
  PID1.SetSampleTime(5);
}


void loop()
{
  motor.update();

  if(fm < millis()) {
  sensors.acquireBNOData();


  Input1 = sensors.getAngle();
  Setpoint1 = 0;
  PID1.Compute();

  Output1 = map(Input1, -180, 180, 950, 2400) + 130;

  if (Output1 > 1500)
  {
    Output1 + 70;
  }
  if (Output1 < 1500)
  {
    Output1 - 70;
  }

  // Serial.print("\t");
  Serial.print(Input1);
  Serial.print("\t");
  Serial.println(Output1);

  motor.setTarget(Output1);
  // sensors.acquireBNOData();


    
    fm = millis() + 400;
  }
}