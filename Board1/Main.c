#include <STC12C5A60S2.H>
#include "BackRoom.h"
#include "Board.h"
#include "uart.h"
#include "mp3.h"

sbit INPUT_DOOR_00 = P0^0;
sbit INPUT_HEAVY_01 = P0^1;
sbit OUTPUT_LOCK_02 = P0^2;//第一个电磁锁
//对应摆放3个
sbit INPUT_PUT_03 = P0^3;
sbit INPUT_PUT_04 = P0^4;
sbit INPUT_PUT_05 = P0^5;

sbit OUTPUT_LOCK_06 = P0^6;//第二个电磁锁
sbit INPUT_AIRBELLOW_07 = P0^7;//拉风箱输入


void Start();
void CheckHeavy();
void Put3();
void CheckClose();
void AirBellow();

void Init()
{
	INPUT_DOOR_00 = 0;
	INPUT_HEAVY_01 = 0;
	OUTPUT_LOCK_02 = 1;
	INPUT_PUT_03 = 0;
	INPUT_PUT_04 = 0;
	INPUT_PUT_05 = 0;
	OUTPUT_LOCK_06 = 1;
	INPUT_AIRBELLOW_07 = 0;
}

void main()
{
	Init();
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
				CheckHeavy();//称重
				break;
			case 2:
				Put3(); //对应摆放3个
				break;
			case 4:
				CheckClose(); //检查上面两个柜门是不是关闭
				break;
			case 5:
				AirBellow();//拉风箱
				break;
		}
	}
}

void Start()
{
	if(INPUT_DOOR_00 == 1)
	{
		delay_ms(8000);
		setStep(1);		
	}
}

void CheckHeavy()
{
	if(INPUT_HEAVY_01 == 1)
	{
		delay_ms(50);
		if(INPUT_HEAVY_01 == 1) //称重
		{
			OUTPUT_LOCK_02 = 0;//打开电磁锁
			setStep(2);
		}
	}
}

void Put3()
{
	if((INPUT_PUT_03 == 1)&&(INPUT_PUT_04 == 1)&&(INPUT_PUT_05 == 1))
	{
		delay_ms(50);
		if((INPUT_PUT_03 == 1)&&(INPUT_PUT_04 == 1)&&(INPUT_PUT_05 == 1))
		{
			OUTPUT_LOCK_06 = 0;//第二个电磁锁断电
			setStep(3);
		}
	}
}

void CheckClose()
{
	if((OUTPUT_LOCK_02 == 1)&&(OUTPUT_LOCK_06 == 1))
	{
		delay_ms(50);
		if((OUTPUT_LOCK_02 == 1)&&(OUTPUT_LOCK_06 == 1))
		{
			Switch_Fan = 1;
			setStep(4);
		}
	}
}

void AirBellow()
{
	if((LastAirBellowStatue == 0)&&(INPUT_AIRBELLOW_07 == 1))
	{
		Air_Bellow_Current_Count++;
	}
	LastAirBellowStatue = LastAirBellowStatue;
}