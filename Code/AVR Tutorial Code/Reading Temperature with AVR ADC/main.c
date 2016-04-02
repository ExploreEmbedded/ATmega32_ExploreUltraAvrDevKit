#include "adc.h"
#include "uart.h"

int main() 
{
    int adcValue;
    int temp;
    
    ADC_Init();       /* Initialize the ADC module */
    UART_Init(9600);  /* Initialize UART at 9600 baud rate */
    
    while(1)
    {
        adcValue = ADC_GetAdcValue(0); // Read the ADC value of channel zero where the temperature sensor(LM35) is connected
        
        /* Convert the raw ADC value to equivalent temperature with 5v as ADC reference
		 Step size of AdC= (5v/1023)=4.887mv = 5mv.
		 for every degree celcius the Lm35 provides 10mv voltage change.
	     1 step of ADC=5mv=0.5'c, hence the Raw ADC value can be divided by 2 to get equivalent temp*/
        
        temp = adcValue/2.0; // Divide by 2 to get the temp value.
        UART_Printf("ADC0 Value:%4d  Equivalent Temperature:%dC\n\r",adcValue,temp);     // Send the value on UART
    }
    
    return (0);
}