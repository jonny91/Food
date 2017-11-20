#include <REGX52.H>
#include "BackRoom.h"
#include "Board.h"
#include "uart.h"
#include "mp3.h"

sbit INPUT_DOOR_00 = P0^0;
sbit INPUT_HEAVY_01 = P0^1;
sbit OUTPUT_LOCK_02 = P0^2;//第一个电磁锁

sbit INPUT_PUT_03 = P0^3;//三个对应摆放
sbit INPUT_PUT_04 = P0^4;
sbit INPUT_PUT_05 = P0^5;

sbit OUTPUT_LOCK_06 = P0^6;//第二个电磁锁
sbit INPUT_CHECKEN_07 = P0^7;//鸡是不是放进去了
sbit INPUT_LOCK_10 = P1^0;//第二个电磁锁是不是关好了

sbit INPUT_AIRBELLOW_11 = P1^1;//拉风箱输入
sbit OUTPUT_LIGHT1_12 = P1^2;
sbit OUTPUT_LIGHT1_13 = P1^3;
sbit OUTPUT_LIGHT1_14 = P1^4;
sbit OUTPUT_LIGHT1_15 = P1^5;

sbit OUTPUT_CHANGE_16 = P1^6;//推杆推出

void Start();
void CheckHeavy();
void Put3();
void CheckClose();
void AirBellow();
void Putter();

void Init()
{
	INPUT_DOOR_00 = 0;
	INPUT_HEAVY_01 = 0;
	OUTPUT_LOCK_02 = 1;
	INPUT_PUT_03 = 0;
	INPUT_PUT_04 = 0;
	INPUT_PUT_05 = 0;
	OUTPUT_LOCK_06 = 1;
	INPUT_CHECKEN_07 = 0;
	INPUT_LOCK_10 = 0;
	INPUT_AIRBELLOW_11 = 0;
	OUTPUT_LIGHT1_12 = 1;
	OUTPUT_LIGHT1_13 = 1;
	OUTPUT_LIGHT1_14 = 1;
	OUTPUT_LIGHT1_15 = 1;
	OUTPUT_CHANGE_16 = 1;
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
			case 3:
				CheckClose(); //检查上面两个柜门是不是关闭
				break;
			case 4:
				AirBellow();//拉风箱
				break;
			case 5:
				Putter();
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
	if((INPUT_CHECKEN_07 == 1)&&(INPUT_LOCK_10 == 1))
	{
		delay_ms(50);
		if((INPUT_CHECKEN_07 == 1)&&(INPUT_LOCK_10 == 1))
		{
			Switch_Fan = 1;
			setStep(4);
		}
	}
}

void AirBellow()
{
	if((LastAirBellowStatue == 0)&&(INPUT_AIRBELLOW_11 == 1))
	{
		Air_Bellow_Current_Count++;
	}
	LastAirBellowStatue = LastAirBellowStatue;
	if(Air_Bellow_Current_Count == 0)
	{
		OUTPUT_LIGHT1_12 = 0;
		OUTPUT_LIGHT1_13 = 0;
		OUTPUT_LIGHT1_14 = 0;
		OUTPUT_LIGHT1_15 = 0;
	}
	if(Air_Bellow_Current_Count == 1)
	{
		OUTPUT_LIGHT1_12 = 1;
		OUTPUT_LIGHT1_13 = 0;
		OUTPUT_LIGHT1_14 = 0;
		OUTPUT_LIGHT1_15 = 0;
	}
	if(Air_Bellow_Current_Count == 2)
	{
		OUTPUT_LIGHT1_12 = 1;
		OUTPUT_LIGHT1_13 = 1;
		OUTPUT_LIGHT1_14 = 0;
		OUTPUT_LIGHT1_15 = 0;
	}
	if(Air_Bellow_Current_Count == 3)
	{
		OUTPUT_LIGHT1_12 = 1;
		OUTPUT_LIGHT1_13 = 1;
		OUTPUT_LIGHT1_14 = 1;
		OUTPUT_LIGHT1_15 = 0;
	}
	if(Air_Bellow_Current_Count >= 4)
	{
		OUTPUT_LIGHT1_12 = 1;
		OUTPUT_LIGHT1_13 = 1;
		OUTPUT_LIGHT1_14 = 1;
		OUTPUT_LIGHT1_15 = 1;
		
		delay_ms(1000);
		setStep(5);
	}
}

void Putter()
{
	OUTPUT_CHANGE_16 = 0;//推杆推出
	delay_ms(1000);
	OUTPUT_LOCK_06 = 0;//电磁锁断电
	setStep(6);
}