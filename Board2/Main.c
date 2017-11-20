#include <STC12C5A60S2.H>
#include "BackRoom.h"
#include "Board.h"
#include "uart.h"
#include "mp3.h"

sbit INPUT_DOOR_00 = P0^0;

sbit INPUT_RC522_01 = P0^1;
sbit INPUT_RC522_02 = P0^2;
sbit INPUT_RC522_03 = P0^3;
sbit INPUT_RC522_04 = P0^4;
sbit INPUT_RC522_05 = P0^5;
sbit INPUT_RC522_06 = P0^6;
sbit INPUT_RC522_07 = P0^7;
sbit INPUT_RC522_10 = P1^0;
sbit INPUT_RC522_11 = P1^1;

sbit OUTPUT_LOCK_12 = P1^2;

sbit INPUT_BUTTON_13 = P1^3;
sbit OUTPUT_BUTTON_14 = P1^4;

sbit Hall_Switch_20 = P2^0;
sbit Hall_Switch_21 = P2^1;
sbit Hall_Switch_LOCK_22 = P2^2;

sbit INPUT_BUTTON_23 = P2^3;//2个霍尔开关打开电磁锁里的按钮
sbit OUTPUT_BUTTON_24 = P2^4;//按钮输出
sbit OUTPUT_Room5_25 = P2^5;//房间5

void Start();
void Check9Input();
void Button();
void HallSwitch();
void Button2();

void init()
{
	INPUT_DOOR_00 = 0;
	
	INPUT_RC522_01 = 0;
	INPUT_RC522_02 = 0;
	INPUT_RC522_03 = 0;
	INPUT_RC522_04 = 0;
	INPUT_RC522_05 = 0;
	INPUT_RC522_06 = 0;
	INPUT_RC522_07 = 0;
	INPUT_RC522_10 = 0;
	INPUT_RC522_11 = 0;
	
	OUTPUT_LOCK_12 = 1;
	INPUT_BUTTON_13 = 0;
	OUTPUT_BUTTON_14 = 1;
	
	Hall_Switch_20 = 0;
	Hall_Switch_21 = 0;
	Hall_Switch_LOCK_22 = 1;
	
	INPUT_BUTTON_23 = 0;
	OUTPUT_BUTTON_24 = 1;
	OUTPUT_Room5_25 = 1;
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
				Start(); //关门开始
				break;
			case 1:
				Check9Input();//检查9个RC522
				break;
			case 2:
				Button();
				break;
			case 3:
				HallSwitch();//2个霍尔开关
				break;
			case 4:
				Button2();
				break;
			case 5:
				break;
		}
	}
}

void Start()
{
	if(INPUT_DOOR_00 == 1)
	{
		delay_ms(50);
		if(INPUT_DOOR_00 == 1)
		{
			setStep(1);
		}
	}
}

void Check9Input()
{
	if((INPUT_RC522_01 == 1)&&
	(INPUT_RC522_02 == 1)&&
	(INPUT_RC522_03 == 1)&&
	(INPUT_RC522_04 == 1)&&
	(INPUT_RC522_05 == 1)&&
	(INPUT_RC522_06 == 1)&&
	(INPUT_RC522_07 == 1)&&
	(INPUT_RC522_10 == 1)&&
	(INPUT_RC522_11 == 1))
	{
		delay_ms(50);
		if((INPUT_RC522_01 == 1)&&
		(INPUT_RC522_02 == 1)&&
		(INPUT_RC522_03 == 1)&&
		(INPUT_RC522_04 == 1)&&
		(INPUT_RC522_05 == 1)&&
		(INPUT_RC522_06 == 1)&&
		(INPUT_RC522_07 == 1)&&
		(INPUT_RC522_10 == 1)&&
		(INPUT_RC522_11 == 1))
		{
			OUTPUT_LOCK_12 = 0;//9个RC522放对位置 打开电磁锁
			setStep(2);
		}
	}
}

void Button()
{
	if(INPUT_BUTTON_13 == 1)
	{
		delay_ms(50);
		if(INPUT_BUTTON_13 == 1)
		{
			OUTPUT_BUTTON_14 = 0;//按下按钮 打开房间5的门
			setStep(3);
		}
	}
}

void HallSwitch()
{
	if((Hall_Switch_20 == 1)&&(Hall_Switch_21 == 1))
	{
		delay_ms(50);
		if((Hall_Switch_20 == 1)&&(Hall_Switch_21 == 1))
		{
			Hall_Switch_LOCK_22 = 0;//打开电磁锁
			setStep(4);
		}
	}
}

void Button2()
{
	if(INPUT_BUTTON_23 == 1)
	{
		delay_ms(50);
		if(INPUT_BUTTON_23 == 1)
		{
			OUTPUT_BUTTON_24 = 0;
			OUTPUT_Room5_25 = 0;//打开房间5
			setStep(5);
		}
	}
}