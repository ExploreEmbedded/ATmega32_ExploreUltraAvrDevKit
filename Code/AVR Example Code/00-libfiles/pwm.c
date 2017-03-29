
/***************************************************************************************************
                                   ExploreEmbedded
 ****************************************************************************************************
 * File:   pwm.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the library function for PWM generation for atmega32 controller

The libraries have been tested on ExploreEmbedded development boards. We strongly believe that the
library works on any of development boards for respective controllers. However, ExploreEmbedded
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information
related to updates.


GNU GENERAL PUBLIC LICENSE:
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
#include "pwm.h"
#include "stdutils.h"




/***************************************************************************************************
                        void PWM_Init(void)
 ****************************************************************************************************
 * I/P Arguments   : none
 * Return value    : none

 * description :This function initializes the Timer2 module for generating the PWM using timers.
 ***************************************************************************************************/
void PWM_Init(uint8_t channel)
{
    switch (channel)
    {
    case 0 :
        TCNT0 = 0x00;
        util_BitSet(DDRB,3); // Make the PWM pin Output
        break;

    case 1 :
        TCNT1 = 0x00;
        util_BitSet(DDRD,5); // Make the PWM pin Output
        break;

    case 2 :
        TCNT1 = 0x00;
        util_BitSet(DDRD,4); // Make the PWM pin Output
        break;

    case 3 :
        TCNT2 = 0x00;
        util_BitSet(DDRD,7); // Make the PWM pin Output
        break;
    }
}







/***************************************************************************************************
                         void PWM_SetDutyCycle( uint8_t channel, uint8_t dutyCycle )
 ****************************************************************************************************
 * I/P Arguments: uint8_t: channel number at which PWM needs to be generated.(0/1).
                  uint8_t : required dutyCycle at the pwm pin(0-100).
 * Return value    : none

 * description :This function is used the set the duty cycle for the required channel.
                Ensure the PWM_Init() function is called before calling this function.
                This function only sets the duty cycle, the actual PWM generation satarts after calling PWM_Start().

Note: By default the dutycyle is set to 50%.
 ***************************************************************************************************/
void PWM_SetDutyCycle(uint8_t channel,uint8_t dutyCycle)
{
       dutyCycle *= 2.55;

    switch (channel)
    {
    case 0 :
        OCR0 = dutyCycle;    //Set the Duty Cycle between 0-100
        break;

    case 1 :
        OCR1A = dutyCycle;    //Set the Duty Cycle between 0-100
        break;

    case 2 :
        OCR1B = dutyCycle;    //Set the Duty Cycle between 0-100
        break;

    case 3 :
        OCR2 = dutyCycle;    //Set the Duty Cycle between 0-100
        break;
    }
}






/***************************************************************************************************
                         void PWM_Start(uint8_t channel)
 ****************************************************************************************************
 * I/P Arguments: none.
 * Return value    : none

 * description :This function is used to start the pwm generation for the required channel.
 ***************************************************************************************************/
void PWM_Start(uint8_t channel)
{
    switch (channel)
    {
    case 0 :
	   TCCR0 = (1<<WGM00)|(1<<COM01)|(1<<CS00); 
        break;

    case 1 :
        util_BitSet(TCCR1A, COM1A1);   //Start the PWM Generation
		util_BitSet(TCCR1A, WGM10);   //Start the PWM Generation
		util_BitSet(TCCR1B, CS10);   //Start the PWM Generation
        break;

    case 2 :
        util_BitSet(TCCR1A, COM1B1);   //Start the PWM Generation
        util_BitSet(TCCR1B, CS10);   //Start the PWM Generation
        break;

    case 3 :
        TCCR2 = (1<<WGM20)|(1<<COM21)|(1<<CS20); 
        break;
    }
}




/***************************************************************************************************
                         void PWM_Start(uint8_t channel)
 ****************************************************************************************************
 * I/P Arguments: none.
 * Return value    : none

 * description :This function is used to stop the pwm generation for the required channel.
 ***************************************************************************************************/
void PWM_Stop(uint8_t channel)
{
    switch (channel)
    {
    case 0 :
        util_BitClear(TCCR0, COM00);   //Stop the PWM Generation
        break;

    case 1 :
        util_BitClear(TCCR1A, COM1A1);   //Stop the PWM Generation
        break;

    case 2 :
        util_BitClear(TCCR1A, COM1B1);   //Stop the PWM Generation
        break;

    case 3 :
        util_BitClear(TCCR2, COM21);    //Stop the PWM Generation
        break;
    }

}
