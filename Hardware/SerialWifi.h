#ifndef SERIAL_WIFI_H
#define SERIAL_WIFI_H
#include <stdint.h>

#define USART1_GPIO_CLK		RCC_APB2Periph_GPIOA
#define USART1_TX_GPIO_PIN 	GPIO_Pin_9
#define USART1_RX_GPIO_PIN 	GPIO_Pin_10
#define USART1_BaudRate 	115200
#define USART3_GPIO_CLK     RCC_APB2Periph_GPIOB
#define USART3_TX_GPIO_PIN 	GPIO_Pin_10
#define USART3_RX_GPIO_PIN 	GPIO_Pin_11
#define USART3_BaudRate 	115200

#define	WRAP_TRUE	1
#define WRAP_FALSE	0
#define USART_PC	1
#define USART_WIFI	3

extern char Serial_PC_RxPacket[];
extern char Serial_Wifi_RxPacket[];

void Serial_TTL2PC_Init(void);
void Serial_Wifi_Init(void);
void Srl_SendByte(uint8_t Usartx, uint8_t Byte);
void Srl_SendString(uint8_t Usartx, char* String);
void Srl_Printf(uint8_t Usartx, uint8_t Line, char* format, ...);
uint8_t Serial_GetRxFlag(uint8_t Usartx);
void Serial_GetRxData(uint8_t Usartx);

void Wifi_IsOK(void);
void Wifi_Restart(void);
void Wifi_SetMode(uint8_t Mode);
void Wifi_SetMulti(uint8_t Mode);
void Wifi_SetWifiInfo(char* SSID, char* Passwd, uint8_t Sec);
void Wifi_StartServer(uint8_t Open, uint16_t Port);
void Wifi_GetSelfIp(void);
void Wifi_GetWifiList(void);
void Wifi_GetDeviceList(void);
void Wifi_ConnectWifi(char* SSID, char* Passwd);
void Wifi_MqttConnect(char* MqttServer, uint16_t MqttPort);
void Wifi_MqttSubscrib(char* Topic);

#endif
