#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Motor.h"

void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	PWM_Init();
}

void Motor_SetSpeed(uint8_t Position, int8_t Speed)
{
	if (Position == TYRE_LEFT)
	{
		if (Speed >= 0)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_3);
			GPIO_ResetBits(GPIOA, GPIO_Pin_4);
			PWM_SetCompare2(Speed);
		}
		else
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_3);
			GPIO_SetBits(GPIOA, GPIO_Pin_4);
			PWM_SetCompare2(-Speed);
		}
	}
	else if (Position == TYRE_RIGHT)
	{
		if (Speed >= 0)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_5);
			GPIO_ResetBits(GPIOA, GPIO_Pin_6);
			PWM_SetCompare3(Speed);
		}
		else
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_5);
			GPIO_SetBits(GPIOA, GPIO_Pin_6);
			PWM_SetCompare3(-Speed);
		}
	}
}

void Motor_Forward(void)
{
	Motor_SetSpeed(TYRE_LEFT, 70);
	Motor_SetSpeed(TYRE_RIGHT, 70);
}

void Motor_Back(void)
{
	Motor_SetSpeed(TYRE_LEFT, -80);
	Motor_SetSpeed(TYRE_RIGHT, -80);
}

void Motor_TurnLeft(void)
{
	Motor_SetSpeed(TYRE_RIGHT, 80);
	Motor_SetSpeed(TYRE_LEFT, 60);
}

void Motor_TurnRight(void)
{
	Motor_SetSpeed(TYRE_LEFT, 80);
	Motor_SetSpeed(TYRE_RIGHT, 60);
}
void Motor_Stop(void)
{
	Motor_SetSpeed(TYRE_LEFT, 0);
	Motor_SetSpeed(TYRE_RIGHT, 0);
}
