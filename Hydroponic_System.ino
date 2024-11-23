#include <Wire.h>
#include "main.h"
#include "ldr.h"
#include "utrasonic.h"
#include "dht11.h"
#include "influxdb.h" 

// Water pump constants
const unsigned long pumpOnTime = 120000;   // 2 minutes
const unsigned long pumpOffTime = 300000;  // 5 minutes
boolean pumpStatus = false;  // Track if the pump is on or off
unsigned long pumpStartTime = 0;
int pump_pin = 12;

void init_pump() {
  pinMode(pump_pin, OUTPUT);
  digitalWrite(pump_pin, LOW);  // Ensure the pump starts off
}

void controlPump() {
  if (pumpStatus) {
    if (millis() - pumpStartTime >= pumpOnTime) {
      digitalWrite(pump_pin, LOW);  // Turn off the pump
      pumpStatus = false;
      Serial.println("Pump off");
      pumpStartTime = millis();  // Reset the timer
    }
  } else {
    if (millis() - pumpStartTime >= pumpOffTime) {
      digitalWrite(pump_pin, HIGH);  // Turn on the pump
      pumpStatus = true;
      Serial.println("Pump on");
      pumpStartTime = millis();  // Reset the timer
    }
  }
}

void setup(void) {
  Serial.begin(9600);

  setupInfluxDB();  // Set up the InfluxDB connection

  init_ldr();  // Initialize the LDR sensor
  init_utrasonic();  // Initialize the ultrasonic sensor
  init_dht11();  // Initialize the DHT11 sensor
  init_pump();  // Initialize the water pump
}

void loop() {
  // Brightness control and data logging
  brightness_control();

  // Read and send DHT11 data to InfluxDB
  read_DHT();

  // Measure distance and add logic for nutrient solution
  measure_distance();

  // Control the water pump with timing logic
  controlPump();
}
