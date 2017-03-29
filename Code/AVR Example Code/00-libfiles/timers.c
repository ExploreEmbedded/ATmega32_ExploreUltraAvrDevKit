/***************************************************************************************************
                                   ExploreEmbedded    
 ****************************************************************************************************
 * File:   timer.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the functions for configuring and using the LPC1768 timers.


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

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timers.h"
#include "stdutils.h"



const uint16_t A_PrescalerTableZeroOne_U8[6]={0,1,8,64,256,1024};
const uint16_t A_PrescalerTableTwo_U8[8]={0,1,8,32,64,128,256,1024};

uint8_t v_Timer0_Prescaler_U8=0;
uint8_t v_Timer0_ReloadValue_U8=0;
uint16_t v_Timer0_OvfCount_U16=0;
isrFunPtr_t Timer0_User_ISR = NULL;

uint8_t v_Timer1_Prescaler_U8=0;
uint16_t v_Timer1_ReloadValue_U16=0;
uint16_t v_Timer1_OvfCount_U16=0;
isrFunPtr_t Timer1_User_ISR = NULL;

uint8_t v_Timer2_Prescaler_U8=0;
uint8_t v_Timer2_ReloadValue_U8=0;
uint16_t v_Timer2_OvfCount_U16=0;
isrFunPtr_t Timer2_User_ISR = NULL;

uint8_t F_OSC = F_CPU/1000000UL;






/*************************************************************************************************
                       Local function declaration
 **************************************************************************************************/
uint8_t getPrescalarValue(uint32_t reqDelay,uint32_t regValue, const uint16_t *ptrPrescalar, uint8_t maxArrayEntries);
/*************************************************************************************************/




/***************************************************************************************************
            void TIMER_Init(uint8_t timerNumber_u8, uint32_t timerIntervalInUs_u32)
 ****************************************************************************************************
 * I/P Arguments: 
                uint8_t: Timer number(TIMER0-TIMER3) that needs to be initialized.
                uint32_t: Timer tick value, Delay time in us.


 * Return value: none

 * description :This function initializes the timer with specfied delay.
                The requested timer should be within rage(TIMER_0,TIMER_3).
                The delay time is multiple of uSec.

 ##Note: This function will only initialize the timers with required delay.
         TIMER_Start() fuctions needs to be called to start the timer.                                  
 ****************************************************************************************************/

void TIMER_Init(uint8_t timerNumber_u8, uint32_t timerIntervalInUs_u32)
{
    TIMER_SetTime(timerNumber_u8,timerIntervalInUs_u32);
}




/***************************************************************************************************
                           void TIMER_Start(uint8_t timerNumber_u8)
 ****************************************************************************************************
 * I/P Arguments: 
                uint8_t: Timer number(TIMER0-TIMER3) that needs to be started.

 * Return value: none

 * description :This function turns on the timer and it starts incrementing.

 ##Note: Before calling the TIMER_Start function the timers should to be initialized by calling TIMER_Init()
 ****************************************************************************************************/
void TIMER_Start(uint8_t timerNumber_u8)
{
    switch(timerNumber_u8)
    {
    case 0 : 
        v_Timer0_OvfCount_U16 = 0;
        TCNT0 = v_Timer0_ReloadValue_U8;       // Load the timer value
        util_BitSet(TIMSK,TOIE0);              //Enable timer interrupt 
        TCCR0 = v_Timer0_Prescaler_U8;         //Start the timer by loading the required presacaler value
        break;



    case 1 : 
        v_Timer1_OvfCount_U16 = 0;
        TCNT1= v_Timer1_ReloadValue_U16;       // Load the timer value
        util_BitSet(TIMSK,TOIE1);              //Enable timer interrupt 
        TCCR1A = 0x00;
        TCCR1B = v_Timer1_Prescaler_U8;        //Start the timer by loading the required presacaler value
        break;



    case 2 : 
        v_Timer2_OvfCount_U16 = 0;
        TCNT2 = v_Timer2_ReloadValue_U8;       // Load the timer value
        util_BitSet(TIMSK,TOIE2);              //Enable timer interrupt 
        TCCR2 = v_Timer2_Prescaler_U8;         //Start the timer by loading the required presacaler value
        break;
    }
}






/***************************************************************************************************
            void TIMER_Stop(uint8_t timerNumber_u8)
 ****************************************************************************************************
 * I/P Arguments: 
                uint8_t: Timer number(TIMER0-TIMER3) that needs to be stopped.

 * Return value: none

 * description :This function turns OFF the timer incrementing.                 
 ****************************************************************************************************/
void TIMER_Stop(uint8_t timerNumber_u8)
{
    switch(timerNumber_u8)
    {
    case TIMER_0 : 
        util_BitSet(TIMSK,TOIE0);              //Disable timer interrupt 
        TCCR0 = v_Timer0_Prescaler_U8;         //Stop the timer by loading the 0x00 as presacaler value
        break;


    case TIMER_1 : 
        util_BitSet(TIMSK,TOIE1);              //Disable timer interrupt 
        TCCR1B = v_Timer1_Prescaler_U8;         //Stop the timer by loading the 0x00 as presacaler value
        break;


    case TIMER_2 : 
        util_BitSet(TIMSK,TOIE2);              //Disable timer interrupt 
        TCCR2 = v_Timer2_Prescaler_U8;         //Stop the timer by loading the 0x00 as presacaler value 
        break;
    }
}





/***************************************************************************************************
            void TIMER_AttachInterrupt(uint8_t timerNumber_u8,timerFunPtr funPtr)
 ****************************************************************************************************
 * I/P Arguments: 
                uint8_t: Timer number(TIMER0-TIMER3) for which the user callback function needs to be hooked.
                timerFunPtr: Function name thats needs to be called by the ISR.
                             The function parameter and return type should be void as shown below.
                             void MyFunToBeCalledByISR(void);

 * Return value: none

 * description :This functions attaches/hookes the user callback function to ISR.
                Ever time the interrupt occurs the ISR will call the user CallBack function.                 
 ****************************************************************************************************/
void TIMER_AttachInterrupt(uint8_t timerNumber_u8,isrFunPtr_t funPtr)
{

    switch(timerNumber_u8)
    {
    case TIMER_0 : 
        Timer0_User_ISR = funPtr;
        break;


    case TIMER_1 : 
        Timer1_User_ISR = funPtr; 
        break;


    case TIMER_2 : 
        Timer2_User_ISR = funPtr; 
        break;
    }
}






/***************************************************************************************************
            uint32_t TIMER_GetTime(uint8_t timerNumber_u8)
 ****************************************************************************************************
 * I/P Arguments: 
                uint8_t: Timer number(TIMER0-TIMER3) whose timer value needs to be read.

 * Return value: uint32_t: Timer/delay value in us.

 * description :This functions returns the current timer value(TC) of the requested timer.                
 ****************************************************************************************************/
uint32_t TIMER_GetTime(uint8_t timerNumber_u8)
{
    uint32_t timerDelay = 0;
    uint16_t prescaler;    
    switch(timerNumber_u8)
    {
    case TIMER_0 : 
        prescaler = A_PrescalerTableZeroOne_U8[v_Timer0_Prescaler_U8];
        timerDelay = (((uint32_t)prescaler * (uint32_t)(256-v_Timer0_ReloadValue_U8))/F_OSC) * v_Timer0_OvfCount_U16;
        if(TCNT0 > v_Timer0_ReloadValue_U8)
        {
            timerDelay = timerDelay  + (((uint32_t)prescaler * (uint32_t)(TCNT0-v_Timer0_ReloadValue_U8))/F_OSC);
        }
        break;


    case TIMER_1 : 
        prescaler = A_PrescalerTableZeroOne_U8[v_Timer1_Prescaler_U8];
        timerDelay = ((prescaler * (65536-v_Timer1_ReloadValue_U16))/F_OSC)* v_Timer1_OvfCount_U16;
        if(TCNT1 > v_Timer1_ReloadValue_U16)
        {
            timerDelay = timerDelay + ((prescaler * (TCNT1-v_Timer1_ReloadValue_U16))/F_OSC);  
        }
        break;


    case TIMER_2 : 
        prescaler = A_PrescalerTableTwo_U8[v_Timer2_Prescaler_U8];
        timerDelay = (((uint32_t)prescaler * (uint32_t)(256-v_Timer2_ReloadValue_U8))/F_OSC) * v_Timer2_OvfCount_U16;
        if(TCNT2 > v_Timer2_ReloadValue_U8)
        {
            timerDelay = timerDelay  + (((uint32_t)prescaler * (uint32_t)(TCNT2-v_Timer2_ReloadValue_U8))/F_OSC);
        }
        break;
    }       

    return timerDelay;
}







/***************************************************************************************************
            void TIMER_SetTime(uint8_t timerNumber_u8, uint32_t timerIntervalInUs_u32)
 ****************************************************************************************************
 * I/P Arguments: 
                uint8_t: Timer number(TIMER0-TIMER3) whose timer value needs to be set.
                uint32_t: Timer/delay value in us.

 * Return value: None 

 * description :This functions sets the required/delay  timer value for the requested timer.                
 ****************************************************************************************************/
void TIMER_SetTime(uint8_t timerNumber_u8, uint32_t timerIntervalInUs_u32)
{
    switch (timerNumber_u8)
    {
    case TIMER_0 : 
        if((timerIntervalInUs_u32 >= TIMER0_MIN_DELAY) && (timerIntervalInUs_u32 <= TIMER0_MAX_DELAY))
        {
            v_Timer0_Prescaler_U8 = getPrescalarValue(timerIntervalInUs_u32,256,A_PrescalerTableZeroOne_U8,6);
            v_Timer0_ReloadValue_U8 =  (uint8_t)256-(uint8_t)((timerIntervalInUs_u32*F_OSC)/(A_PrescalerTableZeroOne_U8[v_Timer0_Prescaler_U8]));
        }
        break;


    case TIMER_1 : 
        if((timerIntervalInUs_u32 >= TIMER1_MIN_DELAY) && (timerIntervalInUs_u32 <= TIMER1_MAX_DELAY))
        {
            v_Timer1_Prescaler_U8 = getPrescalarValue(timerIntervalInUs_u32,65536,A_PrescalerTableZeroOne_U8,6);
            v_Timer1_ReloadValue_U16 =  (uint32_t)65536-((timerIntervalInUs_u32*F_OSC)/(A_PrescalerTableZeroOne_U8[v_Timer1_Prescaler_U8]));
        }
        break;


    case TIMER_2 : 
        if((timerIntervalInUs_u32 >= TIMER2_MIN_DELAY) && (timerIntervalInUs_u32 <= TIMER2_MAX_DELAY))
        {
            v_Timer2_Prescaler_U8 = getPrescalarValue(timerIntervalInUs_u32,256,A_PrescalerTableTwo_U8,8);
            v_Timer2_ReloadValue_U8 =  256-((timerIntervalInUs_u32*F_OSC)/(A_PrescalerTableTwo_U8[v_Timer2_Prescaler_U8]));
        }
        break;
    }
}


extern volatile uint8_t value;

/***************************************************************************************************
                            TIMER_ISR's
 ****************************************************************************************************
 desc: The four ISR's will be called independently whenever the configured delay time is elapsed.
       In other words the ISR's will be called when the Timer Count(TC) reaches the Match Value(MR0).

       The ISR will clear the Interrupt bit as it is being served.(Setting the bit will clear the Corresponding ISR Bit)
       If the user CallBack Function is configured then it will be called.                                  
 ****************************************************************************************************/
ISR (TIMER0_OVF_vect)    // Timer0 ISR
{
	
    TCNT0 = v_Timer0_ReloadValue_U8;
    v_Timer0_OvfCount_U16++;

    if(Timer0_User_ISR != NULL)
    {
        Timer0_User_ISR();
    }
}


ISR (TIMER1_OVF_vect)    // Timer0 ISR
{
    TCNT1 = v_Timer1_ReloadValue_U16;
    v_Timer1_OvfCount_U16++;

    if(Timer1_User_ISR != NULL)
    {
        Timer1_User_ISR();
    }
}


ISR (TIMER2_OVF_vect)    // Timer0 ISR
{
    TCNT2 = v_Timer2_ReloadValue_U8;
    v_Timer2_OvfCount_U16++;
    if(Timer2_User_ISR != NULL)
    {
        Timer2_User_ISR();
    }
}

/*************************************************************************************************
                                    END of  ISR's 
 *************************************************************************************************/




uint8_t getPrescalarValue(uint32_t reqDelay,uint32_t regValue, const uint16_t *ptrPrescalar, uint8_t maxArrayEntries)
{
    uint32_t delay=0;
    uint8_t i;

    for(i=1;i<maxArrayEntries;i++)
    {
        delay = (regValue*ptrPrescalar[i])/F_OSC;
        if(delay >= reqDelay)
            break;
    }
    return i;
}


