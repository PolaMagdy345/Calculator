#define KEYPAD_PRG	1
#include "StdTypes.h"
#include "DIO_Interface.h"
#include "KeyPad_Interface.h"
#include "KeyPad_Cfg.h"
#define F_CPU 8000000
#include <util/delay.h>

void KEYPAD_Init(void)
{
	u8 r;
	for(r=0;r<ROWS;r++)
	{
		DIO_WritePin(FIRST_OUTPUT+r,HIGH);
	}	
}
u8 KEYPAD_Getkey(void)
{
	u8 r,c,key=NO_KEY;
	for(r=0;r<ROWS;r++)
	{
		DIO_WritePin(FIRST_OUTPUT+r,LOW);
		for(c=0;c<COLS;c++)
		{
			if(DIO_ReadPin(FIRST_INPUT+c)==LOW)
			{
				key=KeysArr[r][c];
				while(DIO_ReadPin(FIRST_INPUT+c)==LOW);
			}
		}
					DIO_WritePin(FIRST_OUTPUT+r,HIGH);

	}
	return key;
}
