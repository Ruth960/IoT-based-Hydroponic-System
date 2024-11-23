// influxdb.h
#ifndef INFLUXDB_H
#define INFLUXDB_H

#if defined(ESP32)
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
#elif defined(ESP8266)
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
#endif

#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

// WiFi and InfluxDB configuration
#define WIFI_SSID "Jain_Employee"
#define WIFI_PASSWORD "Employee$1"

#define INFLUXDB_URL "https://us-east-1-1.aws.cloud2.influxdata.com"
#define INFLUXDB_TOKEN "oFlkLEDAgzgGXgg3QRI17yjQVffXEhs36gNXbMSQ6yomzmi_mA7T7jxe_DACcd_MUty7FCFK9KTsA9XvzjDeAg=="
#define INFLUXDB_ORG "cb1ba97b409f647f"
#define INFLUXDB_BUCKET "sensors data"

// Time zone info
#define TZ_INFO "UTC+5:30"

// Declare InfluxDB client instance
extern InfluxDBClient client;

void setupInfluxDB();
void writeSensorData(Point& sensor, float value);  // Write sensor data to InfluxDB

#endif
