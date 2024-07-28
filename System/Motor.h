#ifndef _MOTOR_H
#define _MOTOR_H

#define TYRE_LEFT	2
#define TYRE_RIGHT	3

void Motor_Init(void);
void Motor_SetSpeed(uint8_t Position, int8_t Speed);
void Motor_Forward(void);
void Motor_Back(void);
void Motor_TurnLeft(void);
void Motor_TurnRight(void);
void Motor_Stop(void);

#endif
