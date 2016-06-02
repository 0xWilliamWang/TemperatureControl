#include "stm32f10x.h"
#include "digital_tube.h"
#include "delay.h"
volatile u16 tmp = 0;
unsigned char code_table[] =
{
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71
};
void digital_tube_init(void)
{
	GPIO_InitTypeDef  GPIO_initStruct;

	/*???? */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);

	/*???GPIO */
	GPIO_initStruct.GPIO_Pin =  GPIO_Pin_2 |GPIO_Pin_3;
	GPIO_initStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_initStruct.GPIO_Mode =  GPIO_Mode_Out_PP;	
	GPIO_Init(GPIOD,&GPIO_initStruct);

	GPIO_initStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2
|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_initStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_initStruct.GPIO_Mode =  GPIO_Mode_Out_PP;	
	GPIO_Init(GPIOE,&GPIO_initStruct);
	
	GPIO_ResetBits(GPIOE, 	GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
}

void disp_all_same(u8 num)
{					 
	GPIOE->ODR = 0xff00;	
	GPIO_SetBits(GPIOD,GPIO_Pin_2);
	GPIO_ResetBits(GPIOD,GPIO_Pin_2);

	GPIOE->ODR = code_table[num];
	GPIO_SetBits(GPIOD,GPIO_Pin_3);
	GPIO_ResetBits(GPIOD,GPIO_Pin_3);
}

void disp_one_num(u8 num, int pos, u8 showPoint)
{
	unsigned char b_p = 1;
	
	GPIOE->ODR = ~(b_p << pos);     		
	GPIO_SetBits(GPIOD,GPIO_Pin_2);
	GPIO_ResetBits(GPIOD,GPIO_Pin_2);

	if(showPoint)
		GPIOE->ODR = code_table[num] |0x80;
    else
		GPIOE->ODR = code_table[num];
	GPIO_SetBits(GPIOD,GPIO_Pin_3);
	GPIO_ResetBits(GPIOD,GPIO_Pin_3);
}

void disp_number(int num)
{
	int i = 0;
	int total = 100;
	int num_old = num;
	
	if (num > 0)
	{
		for (total = 500; total > 0;total--)
		{
			i = 0;
			num = num_old;
			while (num > 0)
			{
				disp_one_num(num%10,i++, 0);
				num = num / 10;
				delay_us(100);
			}
		}
	}
}

void show_adc(float VAL)
{
		
		tmp = (u16)((VAL + 0.005) * 100);
		disp_one_num((u8)(tmp%10), 7, 0);
		delay_us(200);
		
		tmp /= 10;
		disp_one_num((u8)(tmp%10), 6, 0);
		delay_us(200);
		
		tmp /= 10;
 		disp_one_num((u8)tmp, 5, 1);
		delay_us(200);	
}
