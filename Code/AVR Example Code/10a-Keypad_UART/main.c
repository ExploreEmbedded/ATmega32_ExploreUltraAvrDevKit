/***************************************************************************************************
                                   ExploreEmbedded	
****************************************************************************************************
 * File:   keypad.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: The files contains the program to read the key pressed on 4x4 hex keypad and send it on UART.

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
#include "uart.h"


int main() 
{
    uint8_t key;
    UART_Init(9600);
	
	/*Connect R1->PB0, R2->PB1, R3->PB2 R4->PB3, C1->PB4, C2->PB5 C3->PB6, C4->PB7 */
    KEYPAD_Init(PB_0,PB_1,PB_2,PB_3,PB_4,PB_5,PB_6,PB_7);
    while (1) 
    {
        key = KEYPAD_GetKey();
        UART_Printf("\n\r Key:%c", key);
    }

    return (0);
}

