#ifndef _MotorDriver_H_
#define _MotorDriver_H_

#define MOTOR_OFF		PTBD= 0x00;

extern unsigned char direction;
extern unsigned int velocidad;

void ControlMotor(void);

#endif

