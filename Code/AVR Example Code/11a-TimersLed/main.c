/*
 * 11a-TimerInterrupts.c
 *
 * Created: 5/12/2016 4:03:15 PM
 * Author : bagwan
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timers.h" 


volatile uint8_t value =0,flag=0;

void  myTimerIsr_0(void)
{
	
	 util_BitToggle(value,0);
}

void  myTimerIsr_1(void)
{
	util_BitToggle(value,1);
/*	value++;
	if(value>=100)
	{
		flag = 1;
	}
	 */
}

void  myTimerIsr_2(void)
{
	util_BitToggle(value,2);
}




int main (void)
{
	
	DDRC= 0xff;
	DDRD= 0xff;
	
	//UART_Init(9600);

	TIMER_Init(0,7500);                  /* Configure timer0 to generate 100ms(100000us) delay*/
	TIMER_AttachInterrupt(0,myTimerIsr_0);  /* myTimerIsr_0 will be called by TIMER0_IRQn */
	TIMER_Start(0);                         /* Start the Timers */
	
	TIMER_Init(1,30000);                  /* Configure timer0 to generate 100ms(100000us) delay*/
	TIMER_AttachInterrupt(1,myTimerIsr_1);  /* myTimerIsr_0 will be called by TIMER0_IRQn */
	// TIMER_Start(1);
	
	TIMER_Init(2,15000);                  /* Configure timer0 to generate 100ms(100000us) delay*/
	TIMER_AttachInterrupt(2,myTimerIsr_2);  /* myTimerIsr_0 will be called by TIMER0_IRQn */
	TIMER_Start(2);
	TIMER_Start(1);
	

	sei();


	while(1)
	{
		
		
		PORTC = value;
		
	}
	
	/*
	{
		if(flag == 1)
		{
			flag = 0;
			TIMER_Stop(0);
			TIMER_Stop(1);
			TIMER_Stop(2);
			
			UART_Printf("Timer0=%8U Timer1:%8U \nTimer2:%8U",TIMER_GetTime(0),TIMER_GetTime(1),TIMER_GetTime(2));
			
		}
	}
	*/

}


