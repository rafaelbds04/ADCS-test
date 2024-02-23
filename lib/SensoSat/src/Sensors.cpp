#include "Sensors.h"

Adafruit_BNO08x bno08x(BNO08X_RESET);

void Sensors::quaternionToEuler(float qr, float qi, float qj, float qk, euler_t *ypr, bool degrees)
{

    float sqr = sq(qr);
    float sqi = sq(qi);
    float sqj = sq(qj);
    float sqk = sq(qk);

    ypr->yaw = atan2(2.0 * (qi * qj + qk * qr), (sqi - sqj - sqk + sqr));
    ypr->pitch = asin(-2.0 * (qi * qk - qj * qr) / (sqi + sqj + sqk + sqr));
    ypr->roll = atan2(2.0 * (qj * qk + qi * qr), (-sqi - sqj + sqk + sqr));

    if (degrees)
    {
        ypr->yaw *= RAD_TO_DEG;
        ypr->pitch *= RAD_TO_DEG;
        ypr->roll *= RAD_TO_DEG;
    }
}

void Sensors::quaternionToEulerRV(sh2_RotationVectorWAcc_t *rotational_vector, euler_t *ypr, bool degrees)
{
    quaternionToEuler(rotational_vector->real, rotational_vector->i, rotational_vector->j, rotational_vector->k, ypr, degrees);
}

Sensors::Sensors()
{
}

void Sensors::initBNOSensor()
{
    // if(!bno08x.begin_I2C(BNO_I2C_ADDRESS, &Wire1)) {
    //     Serial.println("Failed to find BNO08x chip");
    // }

    // while (!Serial)
        // delay(10); // will pause Zero, Leonardo, etc until serial console opens

    delay(4000);
    Serial.println("Adafruit BNO08x test!");

    // Try to initialize!
    if (!bno08x.begin_I2C(BNO_I2C_ADDRESS, &Wire1))
    // {
    //     // if (!bno08x.begin_UART(&Serial1)) {  // Requires a device with > 300 byte UART buffer!
    //     // if (!bno08x.begin_SPI(BNO08X_CS, BNO08X_INT)) {
    //     Serial.println("Failed to find BNO08x chip");
    //     while (1)
    //     {
    //         delay(10);
    //     }
    // }

    while(!bno08x.begin_I2C(BNO_I2C_ADDRESS, &Wire1)) {
        
    }

    Serial.println("BNO08x Found!");

    setReports();

    Serial.println("Reading events");
    delay(100);
}

void Sensors::initAllSensors()
{
    initBNOSensor();
}

void Sensors::setReports(void)
{
    if (!bno08x.enableReport(BNO_reportType, BNOreportIntervalUs))
    {
        Serial.println("Could not enable stabilized remote vector");
    }
}

double Sensors::getAngle()
{
    return IMUData.yaw;
}

void Sensors::acquireBNOData()
{
    if (bno08x.getSensorEvent(&sensorValue))
    {
        // in this demo only one report type will be received depending on FAST_MODE define (above)

        quaternionToEulerRV(&sensorValue.un.arvrStabilizedRV, &IMUData, true);

        // static long last = 0;
        // long now = micros();
        // Serial.print(now - last);
        // Serial.print("\t");
        // last = now;
        // Serial.print(sensorValue.status);
        // Serial.print("\t"); // This is accuracy in the range of 0 to 3
        // Serial.print(IMUData.yaw);
        // Serial.print("\t");
        // Serial.print(IMUData.pitch);
        // Serial.print("\t");
        // Serial.println(IMUData.roll);
    }
}
