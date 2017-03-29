/***************************************************************************************************
                                   ExploreEmbedded
****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This file contains the program to demonstrate the LED Fading depending on PWM duty Cycle. 

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
#include "pwm.h"
#include "delay.h"
#include "stdutils.h"
#include <avr\io.h>


/* start the main program */
int main() 
{
    int dutyCycle;

    PWM_Init(0);
    PWM_Init(1);
	PWM_Init(2);
	PWM_Init(3);
	
	            PWM_SetDutyCycle(0,20);
	            PWM_SetDutyCycle(1,40);
	            PWM_SetDutyCycle(2,60);
	            PWM_SetDutyCycle(3,80);
    
	PWM_Start(0); 
    PWM_Start(1); 
    PWM_Start(2);
	PWM_Start(3); 








    while(1);
    {

        for(dutyCycle=0;dutyCycle<100;dutyCycle++) /* Increase the Brightness of the Leds */
        {
            PWM_SetDutyCycle(0,dutyCycle);  
			PWM_SetDutyCycle(1,dutyCycle);  
			PWM_SetDutyCycle(2,dutyCycle);
			PWM_SetDutyCycle(3,dutyCycle); 
            DELAY_ms(10);
        }

        for(dutyCycle=100;dutyCycle>0;dutyCycle--) /* Decrease the Brightness of the Leds */
        {
            PWM_SetDutyCycle(0,dutyCycle);
            PWM_SetDutyCycle(1,dutyCycle);
            PWM_SetDutyCycle(2,dutyCycle);
            PWM_SetDutyCycle(3,dutyCycle); 
            DELAY_ms(10);
        }
    }                              
}
