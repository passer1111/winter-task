#include "stm32f10x.h"
#include "foot.h"
#include "delay.h"

void pwm_init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//¸´ÓÃÒý½Åpwm
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;//pwm
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;		//GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;		//GPIO_Pin_15
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;		//GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;		//GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;//pwm
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 200 - 1;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
}

void set_foot(uint8_t mark,uint8_t angle)
{
	uint8_t a=0;
	a=angle/9+5;
	if(mark==1)
	{
		TIM_SetCompare1(TIM2,a);
	}
	else if(mark==2)
	{
		TIM_SetCompare2(TIM2,a);
	}
	else if(mark ==3)
	{
		TIM_SetCompare3(TIM2,a);
	}
	else if(mark==4)
	{
		TIM_SetCompare4(TIM2,a);
	}
}

void forward(void)
{
	static uint8_t flag_forward=0;
	for(uint8_t i=0;i<3;i++)
	{
		if(flag_forward==0)
		{
	  set_foot(front_left,90);
		set_foot(front_right,135);
		set_foot(back_left ,45);
		set_foot(back_right,90);
		delay_ms (100);
		set_foot(front_left,45);
		set_foot(front_right,135);
		set_foot(back_left,45);
		set_foot(back_right ,135);
		delay_ms(100);
		set_foot(front_left,45);
		set_foot(front_right,90);
		set_foot(back_left,90);
		set_foot(back_right ,135);
		delay_ms (100);
		set_foot(front_left,90);
		set_foot(front_right,90);
		set_foot(back_left,90);
		set_foot(back_right ,90);
		delay_ms(100);
		flag_forward=1;
		}
		else if(flag_forward==1)
		{
		set_foot(front_left,135);
		set_foot(front_right,90);
		set_foot(back_left,90);
		set_foot(back_right ,45);
		delay_ms(100);
		set_foot(front_left,135);
		set_foot(front_right,45);
		set_foot(back_left,135);
		set_foot(back_right ,45);
		delay_ms(100);
		set_foot(front_left,90);
		set_foot(front_right,45);
		set_foot(back_left,135);
		set_foot(back_right ,90);
		delay_ms(100);
		set_foot(front_left,90);
		set_foot(front_right,90);
		set_foot(back_left,90);
		set_foot(back_right ,90);
		delay_ms(100);
		flag_forward=0;
		}
	}
}

void backward(void)
{
	static uint8_t flag_backward=0;
	for(uint8_t i=0;i<3;i++)
	{
		if(flag_backward ==0)
		{
		set_foot(front_left,45);
		set_foot(front_right,90);
		set_foot(back_left,90);
		set_foot(back_right ,135);
		delay_ms (100);
		set_foot(front_left,45);
		set_foot(front_right,90);
		set_foot(back_left,90);
		set_foot(back_right ,135);
		delay_ms (100);
		set_foot(front_left,90);
		set_foot(front_right,135);
		set_foot(back_left ,45);
		set_foot(back_right,90);
		delay_ms (100);
		set_foot(front_left,90);
		set_foot(front_right,90);
		set_foot(back_left,90);
		set_foot(back_right ,90);
		delay_ms(100);
		flag_backward=1;
		}
		else if(flag_backward ==1)
		{
		set_foot(front_left,90);
		set_foot(front_right,45);
		set_foot(back_left,135);
		set_foot(back_right ,90);
		delay_ms(100);
		set_foot(front_left,135);
		set_foot(front_right,45);
		set_foot(back_left,135);
		set_foot(back_right ,45);
		delay_ms(100);
		set_foot(front_left,135);
		set_foot(front_right,90);
		set_foot(back_left,90);
		set_foot(back_right ,45);
		delay_ms(100);
		set_foot(front_left,90);
		set_foot(front_right,90);
		set_foot(back_left,90);
		set_foot(back_right ,90);
		delay_ms(100);
		flag_backward =0;
		}
	}
}

void right(void)
{
	for(uint8_t i=0;i<3;i++)
	{
		set_foot(front_left,90);
		set_foot(front_right,45);
		set_foot(back_left,45);
		set_foot(back_right ,90);
		delay_ms(100);
		set_foot(front_left,45);
		set_foot(front_right,45);
		set_foot(back_left,45);
		set_foot(back_right ,45);
		delay_ms(100);
		set_foot(front_left,45);
		set_foot(front_right,90);
		set_foot(back_left,90);
		set_foot(back_right ,45);
		delay_ms(100);
		set_foot(front_left,90);
		set_foot(front_right,90);
		set_foot(back_left,90);
		set_foot(back_right ,90);
		delay_ms(100);
	}
}

void left(void)
{
	for(uint8_t i=0;i<3;i++)
	{
		set_foot(front_left,45);
		set_foot(front_right,90);
		set_foot(back_left,90);
		set_foot(back_right ,45);
		delay_ms(100);
		set_foot(front_left,45);
		set_foot(front_right,45);
		set_foot(back_left,45);
		set_foot(back_right ,45);
		delay_ms(100);
		set_foot(front_left,90);
		set_foot(front_right,45);
		set_foot(back_left,45);
		set_foot(back_right ,90);
		delay_ms(100);
		set_foot(front_left,90);
		set_foot(front_right,90);
		set_foot(back_left,90);
		set_foot(back_right ,90);
		delay_ms(100);
	}
}



