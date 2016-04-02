#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRC = 0xff;           // Configure PORTC as output

	while(1)
	{
		PORTC = 0xff;        // Turn ON all the Leds connected to PORTC
		_delay_ms(5000);      // Wait for some time
		PORTC = 0x00;        // Turn OFF all the Leds connected to PORTC
		_delay_ms(5000);      // Wait for some time
	}
	return 0;
}