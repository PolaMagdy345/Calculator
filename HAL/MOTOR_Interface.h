#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

typedef enum{
	M1,
	M2,
	M3,
	M4
}MOTOR_type;
typedef enum{
	STOP,
	CW,
	CCW
	}MOTOR_State;
void MOTOR_Stop(MOTOR_type m);
void MOTOR_CW(MOTOR_type m);
void MOTOR_CCW(MOTOR_type m);
void MOTOR_Init(void);
#endif /* MOTOR_INTERFACE_H_ */