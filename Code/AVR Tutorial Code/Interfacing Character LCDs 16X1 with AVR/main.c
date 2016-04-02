 #include "lcd.h"
 int main()

 { 
	 
	 /*Connect RS->PB0, RW->PB1, EN->PB2 and data bus to PORTC.4 to PORTC.7*/ 
	 LCD_SetUp(PB_0,PB_1,PB_2,P_NC,P_NC,P_NC,P_NC,PC_4,PC_5,PC_6,PC_7);
	 
	 LCD_Init(1,16); 
	  
	 LCD_DisplayString("Explore Embedded");
	  
	 while(1); 
	   
	 return (0); 
	   
} 