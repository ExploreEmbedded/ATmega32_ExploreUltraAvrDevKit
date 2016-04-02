/*
 * Interfacing Character LCDs 20X4 with AVR.c
 *
 * Created: 02-Apr-16 12:19:41 PM
 * Author : exploreembedded
 */ 

#include <avr/io.h>
#include "lcd.h"

 int main() 
 
 { /*Connect RS->PB0, RW->PB1, EN->PB2 and data bus to PORTC.4 to PORTC.7*/
	  LCD_SetUp(PB_0,PB_1,PB_2,P_NC,P_NC,P_NC,P_NC,PC_4,PC_5,PC_6,PC_7); 	  
	  LCD_Init(4,20); 	   
	  LCD_DisplayString("Explore Embedded\n"); 
	  LCD_DisplayString("LCD 4-bit Mode\n"); 
	  LCD_DisplayString("20 x 4 \n"); 
	  LCD_DisplayString(":)  :O");  
	  while(1);  
	  
		 return (0); 
 }

