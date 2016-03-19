#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include "lcd.h"

volatile int cnt_zero,cnt_one;

ISR (INT0_vect)          //External interrupt_zero ISR
{
	cnt_zero++;
}

ISR (INT1_vect)        //External interrupt_one ISR
{
	cnt_one++;
	
}

int main()
{
	DDRC=0xff;   //Configure PORTC(Lcd databus) as output
	DDRD=0xe0;   //Configure INT0,INT1 as input and PORTD5-PORTD7(rs,rw,en) as output
	
	LCD_SetUp(PB_0,PB_1,PB_2,P_NC,P_NC,P_NC,P_NC,PB_4,PB_5,PB_6,PB_7);
	LCD_Init(2,16);
	
	GICR=0xc0;   //Enable External Interrupts INT0 and INT1
	MCUCR=0x08;  //Configure INT0 active low level triggered and INT1 as falling edge
	
	sei();     // Enable global interrupts by setting global interrupt enable bit in SREG
	
	while(1)
	{
		LCD_Printf("EINT0:%4u\n",cnt_zero);
		LCD_Printf("EINT1:%4u\n",cnt_one);
	}
}
