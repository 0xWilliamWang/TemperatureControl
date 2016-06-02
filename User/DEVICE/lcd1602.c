#include "LCD1602.h"
#include "delay.h"
#include "string.h"
void LCD1602_Configuration(void)
{
  delay_init();
	LCD1602_RCC_Configuration();
	LCD1602_GPIO_Configuration();
	delay_ms(400);
  LCD1602_WriteCommand(0x38);
	LCD1602_WriteCommand(0x0c);
	LCD1602_WriteCommand(0x06);
	LCD1602_WriteCommand(0x01);
}

void LCD1602_RCC_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
}
void LCD1602_GPIO_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5| GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void LCD1602_WriteCommand(u8 command)
{
	GPIO_ResetBits(GPIOD,GPIO_Pin_6);
	GPIO_ResetBits(GPIOD,GPIO_Pin_5);
	delay_ms(5);
	GPIO_SetBits(GPIOD,GPIO_Pin_7);
	delay_ms(5);
	GPIOC->ODR = command;
	delay_ms(5);
	GPIO_ResetBits(GPIOD,GPIO_Pin_7);
}

void LCD1602_WriteData(u8 data)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_5);
	GPIOC->ODR = data;
	GPIO_SetBits(GPIOD,GPIO_Pin_7);
	delay_ms(10);
	GPIO_ResetBits(GPIOD,GPIO_Pin_7);
}
void LCD1602_show_str(const char *str,int line)
{
	LCD1602_Configuration();
  LCD1602_WriteCommand(0x80);
	while(*str != '\0')
	{
		LCD1602_WriteData(*str);
		//delay_ms(500);
		str++;
  }
}
