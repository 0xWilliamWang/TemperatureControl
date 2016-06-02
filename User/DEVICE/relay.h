#ifndef __RELAY_H
#define __RELAY_H

#include "stm32f10x.h"
#include "sys.h"

void relay_Init(void);

#define RELAY PDout(7)
#define RELAYON 1
#define RELAYOFF 0 

#endif
