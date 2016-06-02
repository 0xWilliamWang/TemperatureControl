#include "alone_keyboard.h"
#include "led.h"
#include "usart1.h"
#include "digital_tube.h"

extern volatile float set_max_boradline;
extern volatile float set_min_boradline;
volatile u32 count = 0;
#define DELAY 200
static void EXTI_Key_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Configure one bit for preemption priority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;            
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
static void EXTI_Key_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* EXTI line gpio config(PD8,PD9,PD10,PD11) */	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource8);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource9);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource10);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource11);

}

void EXTI_Key_init(void)
{	
	EXTI_InitTypeDef EXTI_InitStructure;												

	/* config the extiline(PD) clock and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO,ENABLE);
	/* config the GPIO(PD) */
	EXTI_Key_GPIO_Configuration();
	/* config the NVIC(PD) */
	EXTI_Key_NVIC_Configuration();

	/* EXTI line mode config */
	EXTI_InitStructure.EXTI_Line = EXTI_Line8|EXTI_Line9|EXTI_Line10|EXTI_Line11;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure); 
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line8) != RESET)
	{
		set_max_boradline+=0.5;
		count = DELAY;
		while(count--)
		{
			show_adc(set_max_boradline);
			printf("\r\n set_max_boradline延时 \r\n");
		}
		EXTI_ClearITPendingBit(EXTI_Line8);
		printf("\r\n set_max_boradline = %f \r\n",set_max_boradline);
	}
	
	if(EXTI_GetITStatus(EXTI_Line9) != RESET)
	{
		set_max_boradline-=0.5;
		count = DELAY;
		while(count--)
		{
			show_adc(set_max_boradline);
			printf("\r\n set_max_boradline延时 \r\n");
		}
		printf("\r\n set_max_boradline = %f \r\n",set_max_boradline);		
		EXTI_ClearITPendingBit(EXTI_Line9);
	}
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line10) != RESET)
	{
		set_min_boradline+=0.5;
		count = DELAY;
		while(count--)
		{
			show_adc(set_min_boradline);
			printf("\r\n set_min_boradline延时 \r\n");
		}
		EXTI_ClearITPendingBit(EXTI_Line10);
		printf("\r\n set_min_boradline = %f \r\n",set_min_boradline);
	}
	
	if(EXTI_GetITStatus(EXTI_Line11) != RESET)
	{
		set_min_boradline-=0.5;
		count = DELAY;
		while(count--)
		{
			show_adc(set_min_boradline);
			printf("\r\n set_min_boradline延时 \r\n");
		}
		EXTI_ClearITPendingBit(EXTI_Line11);
		printf("\r\n set_min_boradline = %f \r\n",set_min_boradline);
	}
}
