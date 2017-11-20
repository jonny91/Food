#include <STC12C5A60S2.H>
#include "BackRoom.h"
#include "Board.h"
#include "uart.h"
#include "mp3.h"

sbit INPUT_A1_00 = P0^0;
sbit INPUT_A2_01 = P0^1;
sbit INPUT_A3_10 = P1^0;
sbit INPUT_A4_11 = P1^1;
sbit INPUT_A5_12 = P1^2;

sbit INPUT_B1_02 = P0^2;
sbit INPUT_B2_03 = P0^3;
sbit INPUT_B3_13 = P1^3;
sbit INPUT_B4_14 = P1^4;
sbit INPUT_B5_15 = P1^5;

sbit OUTPUT_A1_20 = P2^0;
sbit OUTPUT_A2_21 = P2^1;
sbit OUTPUT_A3_24 = P2^4;
sbit OUTPUT_A4_25 = P2^5;
sbit OUTPUT_A5_26 = P2^6;

sbit OUTPUT_B1_22 = P2^2;
sbit OUTPUT_B2_23 = P2^3;
sbit OUTPUT_B3_27 = P2^7;
sbit OUTPUT_B4_04 = P0^4;
sbit OUTPUT_B5_05 = P0^5;

sbit OUTPUT_DOOR = P0^6;

int A_Count = 0;
int B_Count = 0;

void Last();

void init()
{
	INPUT_A1_00 = 0;
	INPUT_A2_01 = 0;
	INPUT_A3_10 = 0;
	INPUT_A4_11 = 0;
	INPUT_A5_12 = 0;	
	
	INPUT_B1_02 = 0;
	INPUT_B2_03 = 0;
	INPUT_B3_13 = 0;
	INPUT_B4_14 = 0;
	INPUT_B5_15 = 0;
	
	OUTPUT_A1_20 = 1;
	OUTPUT_A2_21 = 1;
	OUTPUT_A3_24 = 1;
	OUTPUT_A4_25 = 1;
	OUTPUT_A5_26 = 1;	
	
	OUTPUT_B1_22 = 1;
	OUTPUT_B2_23 = 1;
	OUTPUT_B3_27 = 1;
	OUTPUT_B4_04 = 1;
	OUTPUT_B5_05 = 1;
	
	OUTPUT_DOOR = 0;
	
	A_Count = 0;
	B_Count = 0;
}
void main()
{
	init();
	uart_init();
	mp3_init();

	delay_ms(100);	
	
	while(1)
	{
		switch(step)
		{
			case 0:
				Last();
				break;
			
			case 1:
				OUTPUT_DOOR = 1;
				break;
		}
	}
}

void Last()
{
		A_Count = 0;
		B_Count = 0;
		if(INPUT_A1_00 == 1)
		{
			delay_ms(50);
			if(INPUT_A1_00 == 1)
			{
				A_Count++;
			}
		}
		if(INPUT_A2_01 == 1)
		{
			delay_ms(50);
			if(INPUT_A2_01 == 1)
			{
				A_Count++;
			}
		}
		if(INPUT_A3_10 == 1)
		{
			delay_ms(50);
			if(INPUT_A3_10 == 1)
			{
				A_Count++;
			}
		}
		if(INPUT_A4_11 == 1)
		{
			delay_ms(50);
			if(INPUT_A4_11 == 1)
			{
				A_Count++;
			}
		}
		if(INPUT_A5_12 == 1)
		{
			delay_ms(50);
			if(INPUT_A5_12 == 1)
			{
				A_Count++;
			}
		}
	
		if(INPUT_B1_02 == 1)
		{
			delay_ms(50);
			if(INPUT_B1_02 == 1)
			{
				B_Count++;
			}
		}
		if(INPUT_B2_03 == 1)
		{
			delay_ms(50);
			if(INPUT_B2_03 == 1)
			{
				B_Count++;
			}
		}
		if(INPUT_B3_13 == 1)
		{
			delay_ms(50);
			if(INPUT_B3_13 == 1)
			{
				B_Count++;
			}
		}
		if(INPUT_B4_14 == 1)
		{
			delay_ms(50);
			if(INPUT_B4_14 == 1)
			{
				B_Count++;
			}
		}
		if(INPUT_B5_15 == 1)
		{
			delay_ms(50);
			if(INPUT_B5_15 == 1)
			{
				B_Count++;
			}
		}
		
		if(A_Count == 0)
		{
			OUTPUT_A1_20 = 1;
			OUTPUT_A2_21 = 1;
			OUTPUT_A3_24 = 1;
			OUTPUT_A4_25 = 1;
			OUTPUT_A5_26 = 1;	
		}
		else if(A_Count == 1)
		{
			OUTPUT_A1_20 = 0;
			OUTPUT_A2_21 = 1;
			OUTPUT_A3_24 = 1;
			OUTPUT_A4_25 = 1;
			OUTPUT_A5_26 = 1;	
		}
		else if(A_Count == 2)
		{
			OUTPUT_A1_20 = 0;
			OUTPUT_A2_21 = 0;
			OUTPUT_A3_24 = 1;
			OUTPUT_A4_25 = 1;
			OUTPUT_A5_26 = 1;	
		}
		else if(A_Count == 3)
		{
			OUTPUT_A1_20 = 0;
			OUTPUT_A2_21 = 0;
			OUTPUT_A3_24 = 0;
			OUTPUT_A4_25 = 1;
			OUTPUT_A5_26 = 1;	
		}
		else if(A_Count == 4)
		{
			OUTPUT_A1_20 = 0;
			OUTPUT_A2_21 = 0;
			OUTPUT_A3_24 = 0;
			OUTPUT_A4_25 = 0;
			OUTPUT_A5_26 = 1;	
		}
		else if(A_Count == 5)
		{
			OUTPUT_A1_20 = 0;
			OUTPUT_A2_21 = 0;
			OUTPUT_A3_24 = 0;
			OUTPUT_A4_25 = 0;
			OUTPUT_A5_26 = 0;	
			
			setStep(1);
			return;
		}	
		
		
		if(B_Count == 0)
		{
			OUTPUT_B1_22 = 1;
			OUTPUT_B2_23 = 1;
			OUTPUT_B3_27 = 1;
			OUTPUT_B4_04 = 1;
			OUTPUT_B5_05 = 1;	
		}
		else if(A_Count == 1)
		{
			OUTPUT_B1_22 = 0;
			OUTPUT_B2_23 = 1;
			OUTPUT_B3_27 = 1;
			OUTPUT_B4_04 = 1;
			OUTPUT_B5_05 = 1;
		}
		else if(A_Count == 2)
		{
			OUTPUT_B1_22 = 0;
			OUTPUT_B2_23 = 0;
			OUTPUT_B3_27 = 1;
			OUTPUT_B4_04 = 1;
			OUTPUT_B5_05 = 1;
		}
		else if(A_Count == 3)
		{
			OUTPUT_B1_22 = 0;
			OUTPUT_B2_23 = 0;
			OUTPUT_B3_27 = 0;
			OUTPUT_B4_04 = 1;
			OUTPUT_B5_05 = 1;
		}
		else if(A_Count == 4)
		{
			OUTPUT_B1_22 = 0;
			OUTPUT_B2_23 = 0;
			OUTPUT_B3_27 = 0;
			OUTPUT_B4_04 = 0;
			OUTPUT_B5_05 = 1;
		}
		else if(A_Count == 5)
		{
			OUTPUT_B1_22 = 0;
			OUTPUT_B2_23 = 0;
			OUTPUT_B3_27 = 0;
			OUTPUT_B4_04 = 0;
			OUTPUT_B5_05 = 0;	
			
			setStep(1);
			return;
		}
}


