/***************************************************************************************************
                                   ExploreEmbedded
****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This file contains the program to demonstrate a four digit decimal up counter. 

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

#define SegOne   0x01
#define SegTwo   0x02
#define SegThree 0x04
#define SegFour  0x08	



int main() {
    char seg_code[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
    int cnt, num, temp,i;

    /* Configure the ports as output */
    DDRB = 0xff; // Data lines
    DDRD = 0xff; // Control signal PORTD0-PORTD3

    while (1) 
    {
        for (cnt = 0x00; cnt <= 9999; cnt++) // loop to display 0-9999
        {
            for (i = 0; i < 100; i++)
            {
                num = cnt;
                temp = num / 1000;
                num = num % 1000;
                PORTD = SegOne; 
                PORTB = seg_code[temp];               
                _delay_ms(1);

                temp = num / 100;
                num = num % 100;
                PORTD = SegTwo; 
                PORTB = seg_code[temp];
                _delay_ms(1);

                temp = num / 10;
                PORTD = SegThree;
                PORTB = seg_code[temp];
                _delay_ms(1);

                temp = num % 10;
                PORTD = SegFour;
                PORTB = seg_code[temp];
                _delay_ms(1);                              
            }
        }
    }
}
