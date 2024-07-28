#include "stm32f10x.h"                  // Device header
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

// 串口功能函数

#define SERIAL_PC_PACK_HEADER	'@'
#define SERIAL_WIFI_PACK_HEADER	'A'

char Serial_PC_RxPacket[150];
uint8_t Serial_PC_RxFlag;
//uint8_t Serial_Wifi_TxPacket[150];
char Serial_Wifi_RxPacket[512];
uint8_t Serial_Wifi_RxFlag;

void Srl_SendByte(uint8_t Usartx, uint8_t Byte)
{
	if (Usartx == 1)
	{
		USART_SendData(USART1, Byte);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	}
	else if (Usartx == 3)
	{
		USART_SendData(USART3, Byte);
		while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
	}
}
void Srl_SendString(uint8_t Usartx, char* String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)
	{
		Srl_SendByte(Usartx, String[i]);
	}
}
void Srl_Printf(uint8_t Usartx, uint8_t Line, char* format, ...)
{
	char String[150] = {0};
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	if (Line == 1)
	{
		strcat(String, "\r\n");
	}
	Srl_SendString(Usartx, String);
}

uint8_t Serial_GetRxFlag(uint8_t Usartx)
{
	if (Usartx == 1)
	{
		if (Serial_PC_RxFlag == 1)
		{
			Serial_PC_RxFlag = 0;
			return 1;
		}
		return 0;
	}
	else if (Usartx == 3)
	{
		if (Serial_Wifi_RxFlag == 1)
		{
			Serial_Wifi_RxFlag = 0;
			return 1;
		}
		return 0;
	}
	return 0;
}
void Serial_GetRxData(uint8_t Usartx)
{
	if (Usartx == 1)
	{
		static uint8_t PCRxState = 0;	  //	接收状态
		static uint8_t PCpRxPacket = 0; //	数组位置
		if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
		{
			uint8_t RxData = USART_ReceiveData(USART1);
			if (PCRxState == 0)
			{
				if (RxData == SERIAL_PC_PACK_HEADER)
				{
					PCRxState = 1;
					PCpRxPacket = 0;
				}
			}
			else if (PCRxState == 1)
			{
				if (RxData == '\r')
				{
					PCRxState = 2;
				}
				else
				{
					Serial_PC_RxPacket[PCpRxPacket] = RxData;
					PCpRxPacket++;
				}
			}
			else if (PCRxState == 2)
			{
				if (RxData == '\n')
				{
					PCRxState = 0;
					Serial_PC_RxPacket[PCpRxPacket] = '\0';
					Serial_PC_RxFlag = 1;
				}
			}
			USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		}
	}
	else if (Usartx == 3)
	{	//	接收wifi模块数据
		static uint8_t WRxState = 0;	  //	接收状态
		static uint8_t WpRxPacket = 0; //	数组位置
		if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
		{
			uint8_t RxData = USART_ReceiveData(USART3);
			
			if (WRxState == 0)
			{
				if (RxData == '\r')
				{
					WRxState = 1;
				}
				else
				{
					Serial_Wifi_RxPacket[WpRxPacket] = RxData;
					WpRxPacket++;
				}
			}
			else if (WRxState == 1)
			{
				if (RxData == '\n')
				{
					WRxState = 0;
					Serial_Wifi_RxPacket[WpRxPacket] = '\0';
					Serial_Wifi_RxFlag = 1;
					WpRxPacket = 0;
				}
			}
			USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		}
	}
}

void USART1_IRQHandler(void)
{
	Serial_GetRxData(1);
}

void USART3_IRQHandler(void)
{
	Serial_GetRxData(3);
}
