#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include "Config.h"
#include "Types.h"

#include <Wire.h>
#include "Adafruit_BNO08x.h"

class Sensors
{
    euler_t IMUData;

private:
    sh2_SensorValue_t sensorValue;
    sh2_SensorId_t BNO_reportType = SH2_GYRO_INTEGRATED_RV;
    long BNOreportIntervalUs = 5000;
    void setReports(void);
    void quaternionToEuler(float qr, float qi, float qj, float qk, euler_t *ypr, bool degrees);
    void quaternionToEulerRV(sh2_RotationVectorWAcc_t *rotational_vector, euler_t *ypr, bool degrees);

    /* data */
public:
    double getAngle();
    Sensors(/* args */);
    void initAllSensors();

    void initBNOSensor();
    void acquireBNOData();
};

#endif