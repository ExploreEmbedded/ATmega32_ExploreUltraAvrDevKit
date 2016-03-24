#include<avr/io.h>
#define LED PD4 

int main()
{
	 uint8_t timerOverflowCount=0;	
	 DDRD=0xff;         //configure PORTD as output	
	 TCNT0=0x00;
	 TCCR0 = (1<<CS00) | (1<<CS02);
	 
	while(1)
	{			
		 while ((TIFR & 0x01) == 0); 
		  TCNT0 = 0x00;
		  TIFR=0x01; //clear timer1 overflow flag		              
		 timerOverflowCount++;		 
		 if (timerOverflowCount>=6)
		 {
			 PORTD ^= (0x01 << LED);			 
			 timerOverflowCount=0;
		 } 		 
	}	
}




