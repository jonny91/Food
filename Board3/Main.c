#include <STC12C5A60S2.H>
#include "BackRoom.h"
#include "Board.h"
#include "uart.h"
#include "mp3.h"

void init()
{
}
void main()
{
	init();
	uart_init();
	mp3_init();

	delay_ms(100);	
	
	while(1)
	{
	}
}