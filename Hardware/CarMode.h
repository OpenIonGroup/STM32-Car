#ifndef __CARMODE_H
#define __CARMODE_H

#define CARMODE_REMOTE	1
#define CARMODE_FOLLOW	2

extern uint8_t CarMode;

void CommonService(void);
void CarMode_RemoteControl(void);
void CarMode_Follow(uint16_t SDistance, uint16_t Distance);

#endif
