/***************************************************************************************************
                                   ExploreEmbedded    
****************************************************************************************************
 * File:   pwm.h
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the function declaration and the preprocessors for configuring and using the 8052 PWM.
                As 8051/52 doesn't have inbuilt PWM, timer2 is used to generate the max of 2PWM ouputs.
                These can be enabled/disabled using the constants PWM_0_ENABLE/PWM_1_ENABLE, setting them to 1/0 will enable/disable the respective PWMs
                The PWM output pin can be set using PWM0_PIN/PWM1_PIN.
                By default the dutycyle is set to 50%.

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
#ifndef _PWM_H_
#define _PWM_H_

#include "stdutils.h"



/*************************************************************************************************
                                Function Prototypes                                
*************************************************************************************************/
void PWM_Init(uint8_t channel);
void PWM_SetDutyCycle(uint8_t channel,uint8_t dutyCycle);
void PWM_Start(uint8_t channel);
void PWM_Stop(uint8_t channel);   
/*************************************************************************************************/
#endif
