/***************************************************************************************************
                                   ExploreEmbedded
****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the code to test the ULTRA AVR board.
                Connect the board to system using USB-to-Serial. 
                Reset the board after which the menu will be displayed, select the required option a follow the steps.

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

#include "uart.h"
#include  "rtc.h" 
#include  "i2c.h"
#include  "lcd.h"
#include "delay.h"
#include "keypad.h"
#include "eeprom.h"
#include "gpio.h"
#include "adc.h"

void gpio_test(void);
void LCD_8bit_test(void);
void LCD_4bit_test(void);
void seg_test(void);
void rtc_test(void);
void adc_test(void);
void keypad_test(void);
void eeprom_test(void);


#define LedOn 0xFF
#define LedOff 0x00
#define SegOne   0x01
#define SegTwo   0x02
#define SegThree 0x04
#define SegFour  0x08




#define SegmentValue     PORTC
#define SegValueDirnReg  DDRC

#define SegmentSlection  PORTB 
#define SegSelectDirnReg DDRB




char mm_option;

/* start the main program */
int main()
{
    UART_Init(9600);
    UART_TxString("\n\rTest menu Utra AVR v1.1\r\n 1:GPIO Blink\r\n 2:LCD 8-bit \n\r 3:LCD 4-bit\n\r 4:7-Segment\n\r 5:RTC\n\r 6:EEPROM\n\r 7:ADC\n\r 8:Keypad \n\r Enter option:");
    UART_TxString("\n\rReset the board after test is done");
    mm_option = UART_RxChar();
    while(1)
    {
        switch(mm_option)
        {
        case '1': gpio_test(); break;
        case '2': LCD_8bit_test(); break;
        case '3': LCD_4bit_test(); break;
        case '4': seg_test(); break;
        case '5': rtc_test(); break;
        case '6': eeprom_test(); break; //eeprom
        case '7': adc_test(); break;
        case '8': keypad_test();break;
        default:break;
        }
    }
}


/******************************************************GPIO TEST*************************************
   Turns ON and OFF all the ports of the 8051 micrcontroller. With the help of this you can  
 *****************************************************GPIO TEST**************************************/

void gpio_test()
{   
    uint8_t i;
    
	UART_Printf("\n\rConnect any IO Pins to buzzer, relays, leds ");
    UART_Printf("\n\rMake connections and hit 'k' to test ");
    while(UART_RxChar()!='k');
	
	DDRA = C_PortOutput_U8;
    DDRB = C_PortOutput_U8;
    DDRC = C_PortOutput_U8;
    DDRD = C_PortOutput_U8; 
             
    while(1)
    {
       for(i=0;i<2;i++)
	   {
	    PORTA = 0xff; /* Turn ON all the leds connected to Ports */
        PORTB = 0xff;
        PORTC = 0xff;
        PORTD = 0xff;
        DELAY_ms(100);
        
        PORTA = 0x00; /* Turn OFF all the leds connected to Ports */
        PORTB = 0x00;
        PORTC = 0x00;
        PORTD = 0x00;
        DELAY_ms(100);
	   }
	   
	   for(i=0;i<8;i++)
	   {
		 PORTA = 1<<i; /* Turn ON and OFF one LED at a time */
         PORTB = 1<<i;
         PORTC = 1<<i;
         PORTD = 1<<i;
		 DELAY_ms(100);
	   }
	   
	   for(i=0;i<8;i++)
	   	{
		   PORTA = 0x80>>i; /* Turn ON and OFF one LED at a time */
		   PORTB = 0x80>>i;
		   PORTC = 0x80>>i;
		   PORTD = 0x80>>i;
		  DELAY_ms(100);
	   	}
    }

}

/******************************************************LCD TEST*************************************
					On board LCD TEST in 8 bit mode.
 *****************************************************LCD TEST**************************************/

void LCD_8bit_test()
{     
    UART_TxString("\n\r LCD DataBus:PC    RS-PB.0  RW-PB.1  EN-PB.2 ");
    UART_Printf("\n\r Make connections and hit 'k' to test ");
    while(UART_RxChar()!='k');
    LCD_SetUp(PB_0,PB_1,PB_2,PC_0,PC_1,PC_2,PC_3,PC_4,PC_5,PC_6,PC_7);
    LCD_Init(2,16);
    DELAY_ms(100);
    LCD_DisplayString("Explore Embedded");
    LCD_DisplayString("Lcd 8-bit Mode");
    while(1);
}



void LCD_4bit_test()
{
    UART_TxString("\n\r LCD DataBus:PC4-PC7    RS-PB.0  RW-PB.1  EN-PB.2 ");
    UART_Printf("\n\r Make connections and hit 'k' to test ");
    while(UART_RxChar()!='k');
    LCD_SetUp(PB_0,PB_1,PB_2,P_NC,P_NC,P_NC,P_NC,PC_4,PC_5,PC_6,PC_7);
    LCD_Init(2,16);
    DELAY_ms(100);
    LCD_DisplayString("Explore Embedded");
    LCD_DisplayString("Lcd 4-bit Mode");
    while(1);
}


/*************************************************SEVEN SEGMENT*************************************
 				Displays numbers 1 2 3 4 on the on-board segments 
 *********************************************************TEST**************************************/

void seg_test()
{  
    unsigned char seg_code[]={0xf9,0xa4,0xb0,0x99};
    UART_TxString("\n\r Segment DataBus: PC Seg select: S1->PB.0 S2->PB.1 S3->PB.2 S4->PB.3  ");
    UART_Printf("\n\rMake connections and hit 'k' to test! ");
    while(UART_RxChar()!='k');
    SegValueDirnReg = C_PortOutput_U8;
    SegSelectDirnReg = C_PortOutput_U8;

    while(1)
    {
        SegmentSlection=SegOne;
        SegmentValue = seg_code[0];
        DELAY_us(10);
        SegmentSlection=SegTwo;
        SegmentValue = seg_code[1];
        DELAY_us(10);
        SegmentSlection=SegThree;
        SegmentValue = seg_code[2];
        DELAY_us(10);
        SegmentSlection=SegFour;
        SegmentValue = seg_code[3];
        DELAY_us(10);
    }
}

/***************************************************RTC DS1307*************************************
 				Displays time on UART, reading from the RTC
 *********************************************************TEST**************************************/

void rtc_test()
{
    rtc_t rtc;
    UART_Printf("\n\rConnections SCL->PC.0 SDA->PC.1");
    UART_Printf("\n\r Make connections and hit 'k' to test! ");
    while(UART_RxChar()!='k');   

    RTC_Init();
    rtc.hour = 0x10; //  10:40:20 am
    rtc.min =  0x40;
    rtc.sec =  0x00;

    rtc.date = 0x01; //1st Jan 2016
    rtc.month = 0x01;
    rtc.year = 0x16;
    rtc.weekDay = 5; // Friday: 5th day of week considering monday as first day.




    /*##### Set the time and Date only once. Once the Time and Date is set, comment these lines
         and reflash the code. Else the time will be set every time the controller is reset*/
    RTC_SetDateTime(&rtc);  //  10:40:20 am, 1st Jan 2016


    /* Display the Time and Date continuously */
    while(1)
    {
        RTC_GetDateTime(&rtc);
        UART_Printf("\n\rtime:%2x:%2x:%2x  \nDate:%2x/%2x/%2x",(uint16_t)rtc.hour,(uint16_t)rtc.min,(uint16_t)rtc.sec,(uint16_t)rtc.date,(uint16_t)rtc.month,(uint16_t)rtc.year);
    }
}

/***************************************************EEPROM*****************************************
 				Writes and Reads a character to and from EEPROM
 *****************************************************TEST*****************************************/
void eeprom_test(void)
{
    unsigned char eeprom_address = 0x00, write_char, read_char;

     UART_Printf("\n\r\n\rInbuilt Eeprom Test. Writing and reading A-Z to and from Eeprom.");

    for(write_char='A';write_char<='Z';write_char++)
    {
        UART_Printf("\n\rEeprom Write: %c    ",write_char); //Print the message on UART
        EEPROM_WriteByte(eeprom_address, write_char); // Write the data at memoryLocation    0x00


        read_char = EEPROM_ReadByte(eeprom_address);  // Read the data from memoryLocation 0x00
        UART_Printf("Eeprom Read: %c",read_char); //Print the message on UART
    }
    
    while (1);    
    
}

/***************************************************ADC *****************************************
 				Reads and displays ADC data from on board sensors.
 *****************************************************TEST*****************************************/
void adc_test()
{ 
    uint16_t temp,light,pot;

    ADC_Init();

    while(1)
    {
        temp = ADC_GetAdcValue(0);
        pot = ADC_GetAdcValue(1);
        light = ADC_GetAdcValue(2);
        UART_Printf("\n\rtemp:%4d pot:%4d light:%4d", temp,pot,light);

    }
}


/***************************************************KEYPAD *****************************************
 				Displays keys pressed on 4x4 keypad on the uart
 *****************************************************TEST*******************************************/
void keypad_test()
{
    uint8_t key;
    UART_Printf("\n\rConnect KeyPad To PortC");
    UART_Printf("\n\rMake connections and hit 'k' to test!");
    while(UART_RxChar()!='k');
    KEYPAD_Init(PC_0,PC_1,PC_2,PC_3,PC_4,PC_5,PC_6,PC_7);
    while(1)
    {
        key = KEYPAD_GetKey();
        UART_Printf("\n\r Key:%c", key);
    }
}













