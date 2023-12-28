#include "MemMap.h"
#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"
#include "MOTOR_Interface.h"
#include "LCD_Interface.h"
#include "Car_Interface.h"
#include "KeyPad_Interface.h"
void WriteIns(u8 ins);

int main(void)
{

	DIO_Init();
	MOTOR_Init();
	LCD_Init();
	KEYPAD_Init();
	//CAR_Init();
	u8 k=NO_KEY,Num_Flag=0,n=0,flag=0,Operation_Continue=0,NEW=0;
	s16 num1=0,num2=0,operation=0;
    while (1)
	{
		k=KEYPAD_Getkey();		/*this program for setting on my KIT***PLEASE DON'T CHANGE CFG*/
		if(k!=NO_KEY)
		{
			if(Num_Flag==0)
			{

				if(k>='0' && k<='9')
				{
					if(flag==1)
					{
						LCD_GoTo(0,0);
						LCD_WriteString((u8*)"        ");
						LCD_GoTo(0,0);
						n=0;
						flag=0;
						num1=0;
					}
					num1=num1*10+(k-'0');
					LCD_WriteChar(k);
					n++;
				}
				else if(k=='=')
				{
					LCD_GoTo(1,0);
					LCD_WriteString((u8*)"        ");
					LCD_GoTo(1,0);
					LCD_WriteNumber(num1);
					LCD_GoTo(0,0);
					flag=1;
				}
				else
				{
					LCD_GoTo(0,n);
					LCD_WriteChar(k);
					operation=k;
					Num_Flag=1;
				}
			}
			if(Num_Flag==1 && k!='C' && NEW==0)
			{
				if(k>='0' && k<='9' && operation==0)
				{
					NEW=1;
				}
				if(Operation_Continue==1 && NEW==0)
				{
					LCD_GoTo(0,0);
					LCD_WriteString((u8*)"        ");
					LCD_GoTo(0,0);
					LCD_WriteNumber(num1);
					if(k!='=')
					{
						operation=k;
						LCD_WriteChar(k);
						num2=0;
						Operation_Continue=0;
					}
					else
					{
						operation=k;
					}
				}
				if(k>='0' && k<='9' && Operation_Continue==0 && NEW==0)
				{
					num2=num2*10+(k-'0');
					LCD_WriteChar(k);
				}
				else if (k=='=')
				{
					switch(operation)
					{
						case '/':
						LCD_GoTo(1,0);
						LCD_WriteString((u8*)"        ");
						LCD_GoTo(1,0);
						num1=num1/num2;
						if(num2==0)
						{
							LCD_WriteString((u8*)"ERROR!");
						}
						else
						{
							LCD_WriteNumber(num1);
						}
						operation=0;
						break;
						
						case '*':
						LCD_GoTo(1,0);
						LCD_WriteString((u8*)"        ");
						LCD_GoTo(1,0);
						num1=num1*num2;
						LCD_WriteNumber(num1);
						operation=0;
						break;
						
						case '+':
						LCD_GoTo(1,0);
						LCD_WriteString((u8*)"        ");
						LCD_GoTo(1,0);
						num1=num1+num2;
						LCD_WriteNumber(num1);
						operation=0;
						break;
						
						case '-':
						LCD_GoTo(1,0);
						LCD_WriteString((u8*)"        ");
						LCD_GoTo(1,0);
						num1=num1-num2;
						LCD_WriteNumber(num1);
						operation=0;
						break;		
					}
						Operation_Continue=1;
				}
			}
			if(NEW==1)
			{
				LCD_Clear();
				LCD_GoTo(0,0);
				Num_Flag=0;
				operation=0;
				num1=0;
				num2=0;
				n=0;
				num1=num1*10+(k-'0');
				LCD_WriteChar(k);
				n++;
				NEW=0;

			}
			if(k=='C')
			{
				LCD_Clear();
				LCD_GoTo(0,0);
				Operation_Continue=0;
				flag=0;
				n=0;
				Num_Flag=0;
				operation=0;
				num1=0;
				num2=0;
			}
		}
	}
}
