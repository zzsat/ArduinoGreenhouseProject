#include "at91sam3x8.h"
#include "system_sam3x.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "Keypad.h"
#include "Display.h"

//Global Variables
volatile int flag = 0, flag1, flag2 = 0;
//extern int status, status2 , tdel,del;
float temperature = 0; // To store recorded Temperature

volatile int flagdate = 0;     

void Init_clockTemp () 
{
  //Don’t forget the PMC
  *AT91C_PMC_PCER = (1 << 12);        // Enable PIOB
  //*AT91C_PMC_PCER = (1 << 11);      // Enable PIOA
  *AT91C_PMC_PCER = (1 << 27);        // Enable TC0
  
  *AT91C_TC0_CMR = (*AT91C_TC0_CMR & 0xFFF0FFF8)|(1 << 17)|(1<<18);          //Select Timer_Clock1 as TCCLK
  
  //*AT91C_PMC_PCER = (1 << 27);        // Enable Timer Counter 1
  //*AT91C_PMC_PCER = (1 << 28);        // Enable Timer Counter 2 
  
  *AT91C_TC0_CCR = 0x5;          //Enable counter and make a sw_reset in TC0_CCR0  
    
  
  *AT91C_PIOB_PER = (1 << 25);        
  
  *AT91C_PIOB_PPUDR = (1 << 25);       //Enable the pin
  *AT91C_PIOB_OER = (1 << 25);
  
  
  *AT91C_PIOB_SODR = (1 << 25);       //Enable the pin
  
  *AT91C_PIOB_CODR = (1 << 25);       //Enable the pin
  //del=1;
  //while(del);
    
  *AT91C_PIOB_SODR = (1 << 25);       //Enable the pin
  
  NVIC_ClearPendingIRQ(TC0_IRQn);     //Enable the interrupt (NVIC) with the inline declared function
  NVIC_SetPriority(TC0_IRQn, 2);      //200?
  NVIC_EnableIRQ(TC0_IRQn); 
  *AT91C_TC0_SR;
}                               

void measure_Temp ()   
{                                           //• Start a mesurement    
  *AT91C_PIOB_OER  = (1 << 25);        // StartPulse
  *AT91C_PIOB_SODR = (1 << 25);       //Enable the pin
  
  *AT91C_PIOB_CODR = (1 << 25);       //Enable the pin
  
  //del=1;
  //while(del);
    
  *AT91C_PIOB_SODR = (1 << 25);       //Enable the pin
  Delay(25);
  *AT91C_PIOB_CODR = (1 << 25); 
                                         
  Delay(25);                            // Delay (25)
  *AT91C_PIOB_SODR = (1 << 25);
  
  *AT91C_PIOB_ODR     = (1<<25);   
  
  *AT91C_TC0_CCR = (1 << 2);            // sw_reset in TC0_CCR0
  
  *AT91C_TC0_SR;                        //Clear old interrupt by read statusreg / For B, not A!
  
  *AT91C_TC0_IER = (1<<6);              //Enable interrupt for LDRBS

};

void TC0_Handler()  
{
  
  *AT91C_TC0_IDR = (1 << 6);		// Disable interrupt LDRBS
  flag = 1; 
}

void record_Temperature()
{
  // Should record every minute
  // -> use systick
    int Rb;
    int Ra;
    int time;

    if (flag2 == 0)                     // Use Systick Or Global Variable For Every Minute
    {

      measure_Temp();
  
      flag2 = 1;  
    }
    else
    {
      if (flag == 1)
      {     
        Rb = (*AT91C_TC0_RB);
        Ra = (*AT91C_TC0_RA);
        
        time = Rb-Ra;
                        
        temperature = (float)((((time * (1/42.0))/5.0)-273.15)-3);   
       
        if (temperature != 0)
        {
            //Alarm();  
            //Data(temperature);                
        }

        //printList(List);        
        //printDigit(temperature);
        flag = 0;
        flag2 = 0;              
      }
    }
}

