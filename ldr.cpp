#include "HardwareSerial.h"
#include "ldr.h"
#include "Arduino.h"
#include "main.h"
#include "influxdb.h"  // Include the InfluxDB header to use the writeSensorData function

unsigned int input;

void init_ldr(void) {
   pinMode(GARDEN_LIGHT, OUTPUT);
}

void brightness_control(void) {
  input = analogRead(LDR_SENSOR);

  input = (1023 - input) / 4;  // Calculate the brightness
  sendLdrDataToInflux(input);  // Send the brightness data to InfluxDB

  for (int i = 0; i <= input; i++) {
    analogWrite(GARDEN_LIGHT, i);
    delay(1000);
  }
}

void sendLdrDataToInflux(unsigned int brightness) {
  Point dataPoint("ldr_brightness");  // Create a data point for the LDR sensor
  dataPoint.addTag("sensor", "LDR");  // Optional tag for sensor identification
  dataPoint.addField("brightness", brightness);  // Add the brightness value
  writeSensorData(dataPoint, brightness);  // Write to InfluxDB
}
