#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f10x.h"
#include "sys.h"
void BEEP_Init(void);

#define BEEP PBout(5)
#define BEEPOFF 0
#define BEEPON 1

#endif
