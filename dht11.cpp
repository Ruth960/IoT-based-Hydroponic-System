#include "HardwareSerial.h"
#include <dht.h>
#include "dht11.h"
#include "influxdb.h"  // Include InfluxDB header to access client and writeSensorData function

dht DHT;  // DHT sensor instance

void init_dht11() {
    pinMode(sensor_pin, INPUT);  // Set the sensor pin to input mode
}

float read_DHT() {
    int readData = DHT.read11(sensor_pin);  // Read data from DHT11
    if (readData != 0) {
        Serial.println("Failed to read DHT11 sensor data");
        return -1;  // Return an error code
    }

    float temperature = DHT.temperature;  // Get temperature from DHT11
    float humidity = DHT.humidity;  // Get humidity from DHT11

    Serial.print("Temperature = ");
    Serial.print(temperature);
    Serial.print("°C ");
    Serial.print("Humidity = ");
    Serial.print(humidity);
    Serial.println("% ");

    // Create data points for temperature and humidity
    Point temp_point("temperature");  // Data point for temperature
    Point humidity_point("humidity");  // Data point for humidity

    // Add tags (optional, to add additional information)
    temp_point.addTag("sensor", "dht11");
    humidity_point.addTag("sensor", "dht11");

    // Write temperature and humidity to InfluxDB
    writeSensorData(temp_point, temperature);
    writeSensorData(humidity_point, humidity);

    return 0;  // Return success
}
