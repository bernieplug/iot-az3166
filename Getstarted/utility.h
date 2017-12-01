#ifndef UTILITY_H
#define UTILITY_H

void parseTwinMessage(const char *);
bool readMessage(int, char *);
void sensorInit(void);
void blinkLED(void);
void blinkSendConfirmation(void);
int getInterval(void);

#endif 
