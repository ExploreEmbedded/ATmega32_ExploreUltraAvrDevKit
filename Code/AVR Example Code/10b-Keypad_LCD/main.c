/***************************************************************************************************
                                   ExploreEmbedded	
****************************************************************************************************
 * File:   keypad.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This files contains the program to read the key pressed on 4x4 hex keypad and display it on LCD.

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

#include "keypad.h"
#include "lcd.h"


int main() 
{
    uint8_t key;

    /*Connect RS->PB0, RW->PB1, EN->PB2 and data bus PORTB.4 to PORTB.7*/
    LCD_SetUp(PB_0,PB_1,PB_2,P_NC,P_NC,P_NC,P_NC,PB_4,PB_5,PB_6,PB_7);
    LCD_Init(2,16);
    
	/*Connect R1->PD0, R2->PD1, R3->PD2 R4->PD3, C1->PD4, C2->PD5 C3->PD6, C4->PD7 */
    KEYPAD_Init(PD_0,PD_1,PD_2,PD_3,PD_4,PD_5,PD_6,PD_7);
    
    LCD_Printf("Key Pressed:");
    while (1) 
    {
        key = KEYPAD_GetKey();
        LCD_GoToLine(1);
        LCD_DisplayChar(key);
        
    }

    return (0);
}

