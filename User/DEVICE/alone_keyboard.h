#ifndef __ALONE_KEYBOARD_H
#define __ALONE_KEYBOARD_H

#include "stm32f10x.h"
#include "sys.h"

void EXTI15_10_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI_Key_init(void);

static void EXTI_Key_GPIO_Configuration(void);
static void EXTI_Key_NVIC_Configuration(void);

#endif
