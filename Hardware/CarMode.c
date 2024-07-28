#include "stm32f10x.h"                  // Device header
#include <string.h>
#include <stdint.h>
#include "CarMode.h"
#include "SerialWifi.h"
#include "Motor.h"
#include "Delay.h"

uint8_t CarMode;

void CommonService(void)
{
	if (Serial_GetRxFlag(USART_PC))
	{
		Srl_Printf(USART_PC, WRAP_FALSE, "Res:");
		Srl_Printf(USART_PC, WRAP_TRUE, "%s", Serial_PC_RxPacket);
		if (strstr(Serial_PC_RxPacket, "AT"))
		{
			Srl_Printf(USART_WIFI, WRAP_TRUE, "%s", Serial_PC_RxPacket);
		}
	}
	if (Serial_GetRxFlag(USART_WIFI))
	{
		Srl_Printf(USART_PC, WRAP_TRUE, "%s", Serial_Wifi_RxPacket);
	}
}

void CarMode_RemoteControl(void)
{
	if (Serial_GetRxFlag(USART_PC))					// 串口获取到数据
	{	
		if (strstr(Serial_PC_RxPacket, "forward"))
		{
			Motor_Forward();
		}
		else if (strstr(Serial_PC_RxPacket, "backward"))
		{
			Motor_Back();
		}
		else if (strstr(Serial_PC_RxPacket, "stop"))
		{
			Motor_Stop();
		}
		else if (strstr(Serial_PC_RxPacket, "leftward"))
		{
			Motor_TurnLeft();
		}
		else if (strstr(Serial_PC_RxPacket, "rightward"))
		{
			Motor_TurnRight();
		}
		else if (strstr(Serial_Wifi_RxPacket, "LED_ON"))
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		}
		else if (strstr(Serial_Wifi_RxPacket, "LED_OFF"))
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
		}
	}
	if (Serial_GetRxFlag(USART_WIFI))				// Wifi数据
	{
		if (strstr(Serial_Wifi_RxPacket, "forward"))
		{
			Motor_Forward();
		}
		else if (strstr(Serial_Wifi_RxPacket, "backward"))
		{
			Motor_Back();
		}
		else if (strstr(Serial_Wifi_RxPacket, "stop"))
		{
			Motor_Stop();
		}
		else if (strstr(Serial_Wifi_RxPacket, "leftward"))
		{
			Motor_TurnLeft();
		}
		else if (strstr(Serial_Wifi_RxPacket, "rightward"))
		{
			Motor_TurnRight();
		}
		else if (strstr(Serial_Wifi_RxPacket, "LED_ON"))
		{
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		}
		else if (strstr(Serial_Wifi_RxPacket, "LED_OFF"))
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
		}
	}
}

void CarMode_Follow(uint16_t SDistance, uint16_t Distance)
{
		if (Distance > SDistance + 5)
		{
			Motor_Forward();
			Delay_ms(75);
		}
		else if (Distance < SDistance - 5)
		{
			Motor_Back();
			Delay_ms(75);
		}
		else
		{
			Motor_Stop();
		}
}
