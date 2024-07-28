#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "SerialWifi.h"
#include "Motor.h"
#include "CarMode.h"
#include "Timer.h"
#include "HCSR04.h"
#include <string.h>

int main(void)
{
	OLED_Init();
	Motor_Init();
	Serial_TTL2PC_Init();
	Serial_Wifi_Init();
//	HCSR04_Init();
	
	OLED_ShowChinese(0, 0, "模式：");
//	CarMode = CARMODE_REMOTE;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructrue;
	GPIO_InitStructrue.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructrue.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructrue.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructrue);
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);
	OLED_Update();
	while(1)
	{
//		CommonService();
//		OLED_ShowNum(0, 16, HCSR04_GetValue(), 3, OLED_8X16);
//		OLED_ShowString(24, 16, "cm", OLED_8X16);
//		OLED_Update();
	if (Serial_GetRxFlag(USART_PC))
	{
		Srl_Printf(USART_PC, WRAP_FALSE, "Res:");
		Srl_Printf(USART_PC, WRAP_TRUE, "%s", Serial_PC_RxPacket);
		if (strstr(Serial_PC_RxPacket, "AT"))
		{
			Srl_Printf(USART_WIFI, WRAP_TRUE, "%s", Serial_PC_RxPacket);
		}
	}
//	if (Serial_GetRxFlag(USART_WIFI))
//	{
//		Srl_Printf(USART_PC, WRAP_TRUE, "%s", Serial_Wifi_RxPacket);
//	}
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
			Srl_Printf(USART_PC, WRAP_FALSE, "yes");
		}
		else if (strstr(Serial_Wifi_RxPacket, "LED_OFF"))
		{
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
		}
	}
//	if (Serial_GetRxFlag(USART_PC))					// 串口获取到数据
//	{	
//		if (strstr(Serial_PC_RxPacket, "forward"))
//		{
//			Motor_Forward();
//		}
//		else if (strstr(Serial_PC_RxPacket, "backward"))
//		{
//			Motor_Back();
//		}
//		else if (strstr(Serial_PC_RxPacket, "stop"))
//		{
//			Motor_Stop();
//		}
//		else if (strstr(Serial_PC_RxPacket, "leftward"))
//		{
//			Motor_TurnLeft();
//		}
//		else if (strstr(Serial_PC_RxPacket, "rightward"))
//		{
//			Motor_TurnRight();
//		}
//		else if (strstr(Serial_Wifi_RxPacket, "LED_ON"))
//		{
//			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
//		}
//		else if (strstr(Serial_Wifi_RxPacket, "LED_OFF"))
//		{
//			GPIO_SetBits(GPIOB, GPIO_Pin_6);
//		}
//	}
	}
}
