#include "influxdb.h"

// Initialize the InfluxDB client with preconfigured certificate
InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

void setupInfluxDB() {
    WiFi.mode(WIFI_STA);
    wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);

    while (wifiMulti.run() != WL_CONNECTED) {
        delay(100);
    }

    timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

    if (!client.validateConnection()) {
        Serial.println("InfluxDB connection failed: " + client.getLastErrorMessage());
    }
}

void writeSensorData(Point& sensor, float value) {
    sensor.addField("value", value);  // Add the sensor value to the data point
    client.writePoint(sensor);  // Write to InfluxDB
}
