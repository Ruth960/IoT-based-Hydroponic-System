#ifndef LDR_H
#define LDR_H


#define LDR_SENSOR       A1
#define GARDEN_LIGHT     3

void init_ldr(void);
void brightness_control(void);
void sendLdrDataToInflux(unsigned int brightness);  // Declare the new function for InfluxDB integration

extern unsigned int input;
#endif
