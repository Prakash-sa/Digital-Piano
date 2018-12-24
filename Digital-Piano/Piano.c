// Piano.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// There are four keys in the piano
// Daniel Valvano
// December 29, 2014

// Port E bits 3-0 have 4 piano keys

#include "Piano.h"
#include "..//tm4c123gh6pm.h"


// **************Piano_Init*********************
// Initialize piano key inputs
// Input: none
// Output: none
void Piano_Init(void){ 
	volatile unsigned long  delay;
	SYSCTL_RCGC2_R |= (1<<4);
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTE_LOCK_R = 0x4C4F434B;   
  GPIO_PORTE_CR_R = 0x1F;
	GPIO_PORTE_AMSEL_R=0x00;
	GPIO_PORTE_PCTL_R=0x00000000;
	GPIO_PORTE_DIR_R = 0x00;
	GPIO_PORTE_AFSEL_R &= ~0x0F;
	//GPIO_PORTE_PUR_R = 0x0F;          
  GPIO_PORTE_DEN_R = 0x0F; 
	
	
  
}
// **************Piano_In*********************
// Input from piano key inputs
// Input: none 
// Output: 0 to 15 depending on keys
// 0x01 is key 0 pressed, 0x02 is key 1 pressed,
// 0x04 is key 2 pressed, 0x08 is key 3 pressed
unsigned long Piano_In(void){
  
  switch(GPIO_PORTE_DATA_R)
	{
		case 0x00 : return 0;
		case 0x01 : return 1;
		case 0x02 : return 2;
		case 0x03 : return 3;
		case 0x04 : return 4;
		case 0x05 : return 5;
		case 0x06 : return 6;
		case 0x07 : return 7;
		case 0x08 : return 8;
		case 0x09 : return 9;
		case 0x0a : return 10;
		case 0x0b : return 11;
		case 0x0c : return 12;
		case 0x0d : return 13;
		case 0x0e : return 14;
		case 0x0f : return 15;
		default : return 0;
	}
}

