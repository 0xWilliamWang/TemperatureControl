/**
  ******************************************************************************
  * @file    main.c
  * @author  iuc
  * @version version 1.0
  * @date    
  * @brief   
  ******************************************************************************
  * @attention
  *	
  *
  ******************************************************************************
  */  
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "alone_keyboard.h"
#include "beep.h"
#include "led.h"
#include "relay.h"
#include "usart1.h"
#include "delay.h"
#include "adc.h"
#include "lcd1602.h"
#include "digital_tube.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile float value = 0.0;
volatile float set_max_boradline = 2.0;
volatile float set_min_boradline = 1.0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  ����stm32�ļ򵥵��¶ȿ���ϵͳ
	* @time 2015��6��5��16:12:13
  * @param  
  * @retval 
  */

int main(void)
{	
	delay_init();
	digital_tube_init();
	ADC_Configuration();
	BEEP_Init();
	EXTI_Key_init();
	relay_Init();
	USART1_Config();
	NVIC_usart_Configuration();	
	while(1)
	{
		value = (float)3.3 * ADC_GetConversionValue(ADC1) / 4096;
		show_adc(value);
		if((value >= set_max_boradline)||(value <= set_min_boradline))
		{
			BEEP = BEEPON;
			printf("\r\n value = %f \r\n",value);
			BEEP = BEEPOFF;
			/* �ڴ˲�Ҫʹ��BEEP = ��BEEP����Ϊ���޷�Ԥ���˳����������ʱ��������״̬*/
			RELAY = RELAYON;	
		}
		else RELAY = RELAYOFF;
	}
}
