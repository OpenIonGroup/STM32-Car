#ifndef __TIMER_H
#define __TIMER_H

#define Trig_Port 		GPIOB
#define Trig_Pin 		GPIO_Pin_5
#define Trig_RCC		RCC_APB2Periph_GPIOB

#define Echo_Port 		GPIOB
#define Echo_Pin 		GPIO_Pin_4
#define Echo_RCC		RCC_APB2Periph_GPIOB

void Timer_Init(void);

#endif
