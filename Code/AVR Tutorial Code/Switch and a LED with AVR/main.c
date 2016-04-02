#include <avr/io.h>

int main()
{
	DDRC = 0xff;           // Configure PORTC as output to connect Leds
	DDRA = 0x00;           // Configure PORTA as INput to connect switches
	PORTA = 0xff;          // Enable The PullUps of PORTA.
	while(1)
	{
		PORTC = PINA;     // Read the switch status and display it on Leds
	}
	return 0;
}
