/*
| Example part of AVR Tutorial Series @ Explore Embedded
| To read the detailed tutorial visit:
| http://exploreembedded.com/wiki/5.AVR_Timer_programming
*/
#include<avr/io.h>
#include <util/delay.h>
#define LED PD4
int main()
{
	DDRD |= (1<<LED) ;         //configure led as outpout
	TCCR1B = (1<<CS10) | (1<<CS12); //set the pre-scalar as 1024
	OCR1A = 1562; 	   //100ms delay
	TCNT1 = 0;
	while(1)
	{
		//If flag is set toggle the led
		while((TIFR & (1<<OCF1A)) == 0);// wait till the timer overflow flag is SET
		PORTD ^= (1<< LED);
		TCNT1 = 0;
		TIFR |= (1<<OCF1A) ; //clear timer1 overflow flag
	}
}