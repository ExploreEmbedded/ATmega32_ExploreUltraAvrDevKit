/***************************************************************************************************
                                   ExploreEmbedded    
****************************************************************************************************
 * File:   timer.h
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the function declaration and the SFR bit number for configuring and using the LPC1768 timers.
                 

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
#ifndef _TIMERS_H_
#define _TIMERS_H_


#include <avr/io.h>
#include "stdutils.h"





/*************************************************************************************************
                         Costants, Structures and Typedefs for timers 							   
**************************************************************************************************/
#define TIMER_0     0
#define TIMER_1     1
#define TIMER_2     2
#define TIMER_MAX   3

/**Min and Max delays in microsecs**/
#define TIMER0_MIN_DELAY   1  
#define TIMER0_MAX_DELAY   16384

#define TIMER1_MIN_DELAY   1
#define TIMER1_MAX_DELAY   4194304

#define TIMER2_MIN_DELAY   1
#define TIMER2_MAX_DELAY   16384

typedef void (*isrFunPtr_t)(void);


/*************************************************************************************************/




/*************************************************************************************************
                                Function Prototypes 							   
*************************************************************************************************/
void TIMER_Init(uint8_t timerNumber_u8, uint32_t timerIntervalInUs_u32);
void TIMER_Start(uint8_t timerNumber_u8);
void TIMER_Stop(uint8_t timerNumber_u8);
void TIMER_AttachInterrupt(uint8_t timerNumber_u8,isrFunPtr_t funPtr);
uint32_t TIMER_GetTime(uint8_t timerNumber_u8);
void TIMER_SetTime(uint8_t timerNumber_u8, uint32_t timerIntervalInUs_u32);      
/*************************************************************************************************/


#endif
