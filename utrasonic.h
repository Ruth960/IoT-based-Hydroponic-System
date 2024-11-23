#ifndef UTRASONIC_H
#define UTRASONIC_H

#define triggerPin  9
#define echoPin     8

void init_utrasonic(void);
int read_distance(void);
void sendUltrasonicDataToInflux(int distance);  // New function declaration for InfluxDB integration

#endif
