#include "WaterPump.h"
#include "Arduino.h"
#include "main.h"
#include "influxdb.h"  // Include InfluxDB integration

void init_waterPump() {
  pinMode(pump_pin, OUTPUT);
  turnOFF();  // Ensure the pump is initially off
}

void turnOn() {
  digitalWrite(pump_pin, HIGH);
  logWaterPumpActivity(true);  // Log pump activation to InfluxDB
}

void turnOFF() {
  digitalWrite(pump_pin, LOW);
  logWaterPumpActivity(false);  // Log pump deactivation to InfluxDB
}

void logWaterPumpActivity(bool isActive) {
  Point dataPoint("water_pump");  // Data point for the water pump
  dataPoint.addTag("state", isActive ? "on" : "off");  // Tag the state (on or off)
  writeSensorData(dataPoint, isActive ? 1.0 : 0.0);  // Write the state to InfluxDB
}
