/***************************************************************************************************
                                   ExploreEmbedded	
****************************************************************************************************
 * File:   gpio.h
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the the gpio pin number configuration and  
                function prototypes for the gpio routines
 
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
 
 
 /***************************************************************************************************
                             Revision History
****************************************************************************************************				   
15.0: Initial version 
***************************************************************************************************/
 
#ifndef _GPIO_H
#define _GPIO_H

#include"stdutils.h"


typedef enum
{
    PA_0,PA_1,PA_2,PA_3,PA_4,PA_5,PA_6,PA_7,
    PB_0,PB_1,PB_2,PB_3,PB_4,PB_5,PB_6,PB_7,
    PC_0,PC_1,PC_2,PC_3,PC_4,PC_5,PC_6,PC_7,
    PD_0,PD_1,PD_2,PD_3,PD_4,PD_5,PD_6,PD_7,
    PE_0,PE_1,PE_2,PE_3,PE_4,PE_5,PE_6,PE_7,
	PF_0,PF_1,PF_2,PF_3,PF_4,PF_5,PF_6,PF_7,
	PG_0,PG_1,PG_2,PG_3,PG_4,PG_5,PG_6,PG_7,
    P_NC = 0xff
}gpioPins_et;






/***************************************************************************************************
                             Function prototypes
***************************************************************************************************/
void GPIO_PinDirection(gpioPins_et enm_pinNumber, uint8_t v_pinDirn_u8);
void GPIO_PinWrite(gpioPins_et enm_pinNumber, uint8_t v_pinValue_u8);
uint8_t GPIO_PinRead(gpioPins_et enm_pinNumber);
/**************************************************************************************************/
#endif