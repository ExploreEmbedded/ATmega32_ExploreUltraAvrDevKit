/*
 * UART.c
 *
 * Created: 25-Mar-16 1:17:59 PM
 * Author : exploreembedded
 */ 

#include <avr/io.h>

void UART_Init(uint32_t v_baudRate_u32)
{
	UCSRB= (1<<RXEN) | (1<<TXEN);                  // Enable Receiver and Transmitter
	UCSRC= (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);   // Async-mode
	UCSRA= 0x00;                 // Clear the UASRT status register
	UART_SetBaudRate(v_baudRate_u32);
}


int main(void)
{
    uint32_t C_MaxBaudRate_U32,C_MinBaudRate_U32;
	
    while (1) 
    {
		
		
		void UART_SetBaudRate(uint32_t v_baudRate_u32)
{
	uint16_t RegValue;
 
	if((v_baudRate_u32 >= C_MinBaudRate_U32) && (v_baudRate_u32<=C_MaxBaudRate_U32))
	{
		/* Check if the requested baudate is within range,
	     If yes then calculate the value to be loaded into baud rate generator. */
		RegValue = M_GetBaudRateGeneratorValue(v_baudRate_u32);
	}
	else
	{
/*Invalid baudrate requested, hence set it to default baudrate of 9600 */
		RegValue = M_GetBaudRateGeneratorValue(9600);
	}
 
	UBRRL = util_ExtractByte0to8(RegValue);
	UBRRH = util_ExtractByte8to16(RegValue);
}
		
    }
}

