#include <STC12C5A60S2.H>
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

sbit INPUT_PUT_17 = P1^7;//道具摆放
sbit OUTPUT_LOCK_20 = P2^0;//电磁锁3

sbit INPUT_BUTTON_21 = P2^1;
sbit OUTPUT_BUTTON_22 = P2^2;//按钮输出

sbit INPUT_SWITCH_23 = P2^3;
sbit INPUT_SWITCH_24 = P2^4;

sbit INPUT_RC522_25 = P2^5;
sbit INPUT_RC522_26 = P2^6;
sbit INPUT_RC522_27 = P2^7;
sbit INPUT_RC522_33 = P3^3;

sbit OUTPUT_LOCK_34 = P3^4;//移动机关正确之后的电磁锁

sbit INPUT_BUTTON_35 = P3^5;
sbit OUTPUT_BUTTON_36 = P3^6;
sbit OUTPUT_LOCK_40 = P4^0;

void Start();
void CheckHeavy();
void Put3();
void CheckClose();
void AirBellow();
void Putter();
void Put();
void Button();
void Switch();
void Move();
void Button2();

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
	INPUT_PUT_17 = 0;
	OUTPUT_LOCK_20 = 1;
	INPUT_BUTTON_21 = 0;
	OUTPUT_BUTTON_22 = 1;
	
	INPUT_SWITCH_23 = 0;
	INPUT_SWITCH_24 = 0;
	
	INPUT_RC522_25 = 0;
	INPUT_RC522_26 = 0;
	INPUT_RC522_27 = 0;
	INPUT_RC522_33 = 0;
	
	OUTPUT_LOCK_34 = 1;
	
	INPUT_BUTTON_35 = 0;
	OUTPUT_BUTTON_36 = 1;
	OUTPUT_LOCK_40 = 1;
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
			case 6:
				Put();//道具摆放
				break;
			case 7:
				Button();
				break;
			case 8://北京皇宫
				Switch();
				break;
			case 9://移动机关
				Move();
				break;
			case 10:
				Button2();
				break;
			case 11:
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

void Put()
{
	if(INPUT_PUT_17 == 1)
	{
		delay_ms(50);
		if(INPUT_PUT_17 == 1)
		{
			OUTPUT_LOCK_20 = 0;//打开电磁锁3
			setStep(7);
		}
	}
}

void Button()
{
	if(INPUT_BUTTON_21 == 1)
	{
		delay_ms(50);
		if(INPUT_BUTTON_21 == 1)
		{
			OUTPUT_BUTTON_22 = 0;
			setStep(8);
		}
	}
}

void Switch()
{
	//机关扭动2个输入高电平
	if((INPUT_SWITCH_23 == 1)&&(INPUT_SWITCH_24 == 1))
	{
		delay_ms(50);
		if((INPUT_SWITCH_23 == 1)&&(INPUT_SWITCH_24 == 1))
		{
			setStep(9);//激活移动机关
		}
	}
}

void Move()
{
	if((INPUT_RC522_25 == 1)&&(INPUT_RC522_26 == 1)&&(INPUT_RC522_27 == 1)&&(INPUT_RC522_33 == 1))
	{
		delay_ms(50);
		if((INPUT_RC522_25 == 1)&&(INPUT_RC522_26 == 1)&&(INPUT_RC522_27 == 1)&&(INPUT_RC522_33 == 1))
		{
			OUTPUT_LOCK_34 = 0;
			setStep(10);
		}
	}
}

void Button2()
{
	if(INPUT_BUTTON_35 == 1)
	{
		delay_ms(50);
		if(INPUT_BUTTON_35 == 1)
		{
			OUTPUT_BUTTON_36 = 0;
			OUTPUT_LOCK_40 = 0;
			setStep(11);
		}
	}

}
