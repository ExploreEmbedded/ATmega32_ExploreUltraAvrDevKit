/***************************************************************************************************
                                   ExploreEmbedded
****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This file contains the program to the on board peripherals of Starter AVR board. 

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


#include <avr\io.h>
#include "adc.h"
#include "delay.h"
#include "gpio.h"
#include "lcd.h"
#include "stdutils.h"
#include "uart.h"
#include "eeprom.h"

#define SWITCH1 PD_2
#define SWITCH2 PD_3
#define LED1    PD_4
#define LED2    PD_5


void led_Test(void);
void lcd_Test(void);
void switch_Test(void);
void adc_Test(void);
void eeprom_Test(void);

int main() 
{
  
    char option; 
      
    UART_Init(9600);
    UART_Printf("\n\r\n\rStarter AVR test Menu\n\r 1.Led test\n\r 2.Lcd test\n\r 3.Switch test\n\r 4.Adc Test\n\r 5.Eeprom Test \n\rSelect One of the above options");
    
    while(1)
    {
        option = UART_RxChar();
        switch(option)
        {
            case '1':
                led_Test();
                break;
                
            case '2':
                lcd_Test();
                break;
                
            case '3':
                switch_Test();
                break;
                
            case '4':
                adc_Test();
                break;
				
		     case '5':
			    eeprom_Test();
			    break;	
                
            default:
                break;    
        }
    }
    return (0);
}


void led_Test(void)
{
    uint8_t i,pattern;
    DDRA = C_PortOutput_U8;
    DDRB = C_PortOutput_U8;
    DDRC = C_PortOutput_U8;
    DDRD = C_PortOutput_U8;
  
    
    while(1)
    {
        
        PORTA = 0xff; /* Turn ON all the leds connected to Ports */
        PORTB = 0xff;
        PORTC = 0xff;
        PORTD = 0xff;
        DELAY_ms(500);
        
        PORTA = 0x00; /* Turn OFF all the leds connected to Ports */
        PORTB = 0x00;
        PORTC = 0x00;
        PORTD = 0x00;
        DELAY_ms(500);
        
        pattern=0x01;
        for(i=0;i<8;i++)
        {
            PORTA = pattern;
            PORTB = pattern;
            PORTC = pattern;
            PORTD = pattern;  
            pattern = pattern<<1;
            DELAY_ms(200);
        }
    }

}



void lcd_Test(void)
{
    LCD_SetUp(PB_0,PB_1,PB_2,P_NC,P_NC,P_NC,P_NC,PC_4,PC_5,PC_6,PC_7);
    LCD_Init(2,16);
    LCD_DisplayString("Explore\n Starter Avr..."); 
    
    while(1);
}





void switch_Test(void)
{
    GPIO_PinDirection(LED1,OUTPUT);
    GPIO_PinDirection(LED2,OUTPUT);
    GPIO_PinDirection(SWITCH1,INPUT);
    GPIO_PinDirection(SWITCH2,INPUT);
    UART_TxString("\n\n\n\rPress the switches and observe the output on Leds");
    while(1)
    {
        GPIO_PinWrite(LED1,GPIO_PinRead(SWITCH1));
        GPIO_PinWrite(LED2,GPIO_PinRead(SWITCH2));        
    }
}




void adc_Test(void)
{
    ADC_Init();
    
    while(1)
    {
        UART_Printf("\n\rADC0 value= %4d",ADC_GetAdcValue(0));
    }            
}


void eeprom_Test(void)
{
    unsigned char eeprom_address = 0x00, write_char = 'X', read_char;

     UART_Printf("\n\r\n\rInbuilt Eeprom Test. Writing and reading A-Z to and from Eeprom.");

    for(write_char='A';write_char<='Z';write_char++)
    {
	    UART_Printf("\n\rEeprom Write: %c    ",write_char); //Print the message on UART
	    EEPROM_WriteByte(eeprom_address, write_char); // Write the data at memoryLocation	0x00


	    read_char = EEPROM_ReadByte(eeprom_address);  // Read the data from memoryLocation 0x00
	    UART_Printf("Eeprom Read: %c",read_char); //Print the message on UART
    }
    
    while (1);	
	
}