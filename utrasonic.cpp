#include "HardwareSerial.h"
#include "utrasonic.h"
#include "Arduino.h"
#include "main.h"
#include "influxdb.h"  // Include the InfluxDB header

void init_utrasonic() {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int read_distance() {
  int duration; 
  int distance;

  // Trigger the ultrasonic pulse
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Read the pulse duration
  duration = pulseIn(echoPin, HIGH);
  distance = 0.0174 * duration;  // Calculate distance

  Serial.print("Distance is ");
  Serial.println(distance);

  sendUltrasonicDataToInflux(distance);  // Send distance data to InfluxDB

  return distance;  // Return the distance
}

void sendUltrasonicDataToInflux(int distance) {
  Point dataPoint("ultrasonic_distance");  // Create a data point for the ultrasonic sensor
  dataPoint.addTag("sensor", "ultrasonic");  // Optional tag for sensor identification
  dataPoint.addField("distance", distance);  // Add the distance value
  writeSensorData(dataPoint, distance);  // Write to InfluxDB
}
