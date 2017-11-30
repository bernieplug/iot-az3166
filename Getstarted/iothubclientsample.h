#ifndef IOTHUBCLIENTSAMPLE_H
#define IOTHUBCLIENTSAMPLE_H

#include "iothub_client_ll.h"

void iothubInit(void);
void iothubSendMessage(const unsigned char *, bool, bool);
void iothubLoop(void);
void iothubClose(void);

extern int messageCount;
#endif 
