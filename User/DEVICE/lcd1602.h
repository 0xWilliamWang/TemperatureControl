#ifndef __LCD1602_H
#define __LCD1602_H
#include "sys.h"

void LCD1602_RCC_Configuration(void);
void LCD1602_GPIO_Configuration(void);
void LCD1602_Configuration(void);
void LCD1602_WriteCommand(u8 command);
void LCD1602_WriteData(u8 data);

void LCD1602_show_str(const char *str,int line);

#endif
