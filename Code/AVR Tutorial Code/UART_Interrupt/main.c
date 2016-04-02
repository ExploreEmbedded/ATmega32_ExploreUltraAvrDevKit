#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include "lcd.h"

volatile char ch,rx_flag=0;

void tx_char()
{
	while((UCSRA & 0x60)==0); // Wait till Transmitter(UDR) register becomes Empty
	UDR =ch;                // Load the data to be transmitted
}

ISR (USART_RXC_vect)
{
	ch=UDR;         // copy the received data into ch
	rx_flag=1;      //flag is set to indicate a char is received
}

int main()
{
	DDRC=0xff;
	DDRD=0xff;
	LCD_SetUp(PB_0,PB_1,PB_2,P_NC,P_NC,P_NC,P_NC,PB_4,PB_5,PB_6,PB_7);
	LCD_Init(2,16);
	
	
	
	UCSRB= 0x98;   // Enable Receiver,Transmitter,Receiver interrupt(RXIE)
	UCSRC= 0x86;   // Asynchronous mode 8-bit data and 1-stop bit
	UCSRA= 0x00;   // Normal Baud rate(no doubling), Single processor commn
	UBRRH= 0;
	UBRRL= 103;     // 9600 Baud rate at 16MHz
	
	sei();    // Enable global interrupts by setting global interrupt enable bit in SREG

	
	
	LCD_DisplayString("Type on  Serial Port:");
	
	while(1)
	{
		if(rx_flag==1)
		{
			LCD_SetCursor(1,5);
			tx_char();
			LCD_DisplayChar(ch);
			rx_flag=0;
		}
	}
}
