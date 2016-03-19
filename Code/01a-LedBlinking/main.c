/***************************************************************************************************
                                   ExploreEmbedded
****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This file contains the program to demonstrate the LED blinking. 

The libraries have been tested on ExploreEmbedded development boards. We strongly believe that the
library works on any of development boards for respective controllers. However, ExploreEmbedded
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information
related to updates.


GNU GENERAL PUBLIC LICENSE:
    Copyright (C) 2012  ExploreEmbedded

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


Errors and omissions should be reported to codelibraries@exploreembedded.com
**************************************************************************************************/


#include <avr/io.h>
#include <util/delay.h>


int main() 
{
	uint8_t i;
  /* Configure all the ports as Output */
    DDRA = 0xff;
    DDRB = 0xff;
    DDRC = 0xff;
    DDRD = 0xff; 
    
    while(1)
    {
       for(i=0;i<2;i++)
	   {
	    PORTA = 0xff; /* Turn ON all the leds connected to Ports */
        PORTB = 0xff;
        PORTC = 0xff;
        PORTD = 0xff;
        _delay_ms(100);
        
        PORTA = 0x00; /* Turn OFF all the leds connected to Ports */
        PORTB = 0x00;
        PORTC = 0x00;
        PORTD = 0x00;
        _delay_ms(100);
	   }
	   
	   for(i=0;i<8;i++)
	   {
		 PORTA = 1<<i; /* Turn ON and OFF one LED at a time */
         PORTB = 1<<i;
         PORTC = 1<<i;
         PORTD = 1<<i;
		  _delay_ms(100);
	   }
	   
	  
	    for(i=0;i<8;i++)
	   	{
		 PORTA = 0x80>>i; /* Turn ON and OFF one LED at a time */
		 PORTB = 0x80>>i;
		 PORTC = 0x80>>i;
		 PORTD = 0x80>>i;
		 _delay_ms(100);
	   	}
		   
    }

    return (0);
}


