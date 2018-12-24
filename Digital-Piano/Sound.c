// Sound.c
// Runs on LM4F120 or TM4C123, 
// edX lab 13 
// Use the SysTick timer to request interrupts at a particular period.
// Daniel Valvano, Jonathan Valvano
// December 29, 2014
// This routine calls the 4-bit DAC

#include "Sound.h"
#include "DAC.h"
#include "..//tm4c123gh6pm.h"

unsigned char Index;  

// 3-bit 16-element sine wave
const unsigned long SineWave16[16] = {8,11,13,14,15,14,13,11,8,5,3,2,1,2,3,5};
const unsigned char SineWave32[32] = {8,9,11,12,13,14,14,15,15,15,14,14,13,12,11,9,8,7,5,4,3,2,2,1,1,1,2,2,3,4,5,7};  // dac.xls
int sound_enable;
// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Also calls DAC_Init() to initialize DAC
// Input: none
// Output: none
void Sound_Init(void){
  DAC_Init();
	Index=0;
	sound_enable=0;
	NVIC_ST_CTRL_R=0;
	NVIC_ST_CURRENT_R=0;
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x20000000;
	NVIC_ST_RELOAD_R = C32; 
	NVIC_ST_CTRL_R = 0x0007;
}

// **************Sound_Tone*********************
// Change Systick periodic interrupts to start sound output
// Input: interrupt period
//           Units of period are 12.5ns
//           Maximum is 2^24-1
//           Minimum is determined by length of ISR
// Output: none
void Sound_Tone(unsigned long period){
// this routine sets the RELOAD and starts SysTick
	sound_enable=1;
	NVIC_ST_RELOAD_R= period ;
	
}


// **************Sound_Off*********************
// stop outputing to DAC
// Output: none
void Sound_Off(void){
 // this routine stops the sound output
	DAC_Out(0x00);
	sound_enable=0;
}


// Interrupt service routine
// Executed every 12.5ns*(period)
void SysTick_Handler(void){
 // GPIO_PORTE_DATA_R ^= 0x08;     // toggle PF3, debugging
  #if defined SIN_32
	Index = (Index+1)&0x1F;  
	if(sound_enable) {
		DAC_Out(SineWave32[Index]);
	}
	#else
	Index = (Index+1)&0x0F;  
	if(sound_enable) {
		DAC_Out(SineWave16[Index]);
	}
	#endif
}
