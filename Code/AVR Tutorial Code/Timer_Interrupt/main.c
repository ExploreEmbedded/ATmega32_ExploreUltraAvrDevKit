#include<avr/io.h>
#include<avr/interrupt.h>

#define led PORTC
volatile char cnt=0x00;

ISR (TIMER1_OVF_vect)    // Timer1 ISR
{
	
	cnt++;          // Increment the cnt value each time the isr is executed
	
	TCNT1H=0xE3;    // Reload the 16-bit count value
	TCNT1L=0xE0;    // in timer1 count registers
}

int main()
{
	DDRC=0xff;     //Configure the PORTC as output
	
	TCNT1H=0xE3;   // Load the 16-bit count value
	TCNT1L=0xE0;   // for 1 sec at 7.3728MHz

	TCCR1A=0x00;
	TCCR1B=0x05;  // Timer mode with 1024 prescler
	TIMSK=0x04;   // Enable timer1 overflow interrupt(TOIE1)
	sei();        // Enable global interrupts by setting global interrupt enable bit in SREG
	
	while(1)
	{
		
		PORTC=cnt; // Send the cnt value to PORTC which will be incremented in timer ISR
		
	}
}



