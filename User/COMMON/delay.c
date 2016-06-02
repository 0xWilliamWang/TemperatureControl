/**
  ******************************************************************************
  * @file    delay.c 
  * @author  联航精英训练营   allen@unigress.com
  * @version V1.0
  * @date    2013-10-20
  * @brief   本源码中实现了基于STM32内部SysTick定时器的精确延时，分别实现了SysTick
  *          定时器的初始化，以及毫秒（ms）、微妙（us）级别的精确延时。
  ******************************************************************************
  * @attention
  *
  * 本程序所提供的源代码均为本程序作者或由网络收集整理而来，仅供学习和研究使用。
  * 如有侵犯的地方，请及时联系，我们会立即修改。使用本程序源码的用户必须明白，
  * 我们不能保证所提供的源码及其它资源的准确性、安全性和完整性，因此我们将不负责
  * 承担任何直接，间接因使用这些源码对自己和他人造成任何形式的损失或伤害。任何人
  * 在使用本代码时，应注明作者和出处。
  *
  * <h2><center>版权所有(C) 2013 太原联航科技有限公司</center></h2>
  ******************************************************************************
  */ 
#include "delay.h"
 
static u8  fac_us = 0;//us延时倍乘数
static u16 fac_ms = 0;//ms延时倍乘数


//初始化延迟函数
//SYSTICK的时钟固定为HCLK时钟的1/8
//SYSCLK:系统时钟
void delay_init()	 
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	fac_us=SystemCoreClock/8000000;	//为系统时钟的1/8  
	 
	fac_ms=(u16)fac_us*1000;//非ucos下,代表每个ms需要的systick时钟数   
}								    

//延时nus
//nus为要延时的us数.		    								   
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	 
}

//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	  	    
} 

/******************* (C) 版权所有 2013 太原联航科技有限公司 *******************/
































