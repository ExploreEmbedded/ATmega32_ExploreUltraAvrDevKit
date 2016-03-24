#include<avr/io.h>
#include<avr/interrupt.h>

#define LED PD4

ISR (TIMER1_OVF_vect)    // Timer1 ISR
{
	PORTD ^= (1 << LED);	
	TCNT1 = 63976;   // for 1 sec at 16 MHz
}

int main()
{
	DDRD = (0x01 << LED);     //Configure the PORTD4 as output
	
	TCNT1 = 63976;   // for 1 sec at 16 MHz	

	TCCR1A = 0x00;
	TCCR1B = (1<<CS10) | (1<<CS12);;  // Timer mode with 1024 prescler
	TIMSK = (1 << TOIE1) ;   // Enable timer1 overflow interrupt(TOIE1)
	sei();        // Enable global interrupts by setting global interrupt enable bit in SREG
	
	while(1)
	{
		
	}
}



