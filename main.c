#include "at91sam3x8.h"
#include "system_sam3x.h"
#include <stdio.h>
#include <stdlib.h>

#include "Display.h"
#include "Keypad.h"
#include "PWM.h"
#include "Systick.h"
#include "Temperature.h"

void Config()
{
  *AT91C_PMC_PCER = (1<<14);//Assignes the number 1 to the 14:th bit, enabling the clock/power for the PIO
  *AT91C_PMC_PCER = (1<<13);//Assignes the number 1 to the 14:th bit, enabling the clock/power for the PIO

  *AT91C_PIOC_PER = (1<<7); // (PIOC) PIO Enable Register PIN 39
  *AT91C_PIOC_OER = (1<<7); // Input enable register
  *AT91C_PIOC_PPUDR = (1<<7);

  *AT91C_PIOC_PER = (1<<8); //PIN 40
  *AT91C_PIOC_OER = (1<<8);
  *AT91C_PIOC_PPUDR = (1<<8);

  *AT91C_PIOC_PER = (1<<9); //PIN 41
  *AT91C_PIOC_OER = (1<<9);
  *AT91C_PIOC_PPUDR = (1<<9);

  *AT91C_PIOD_PER = (1<<2);     //PIN 27
  *AT91C_PIOD_OER = (1<<2);
  *AT91C_PIOD_PPUDR = (1<<2);

  *AT91C_PIOC_PER = (1<<5);     //PIN 37
  *AT91C_PIOC_ODR = (1<<5);
  *AT91C_PIOC_PPUDR = (1<<5);

  *AT91C_PIOC_PER = (1<<4);     //PIN 36
  *AT91C_PIOC_ODR = (1<<4);
  *AT91C_PIOC_PPUDR = (1<<4);

  *AT91C_PIOC_PER = (1<<3);     //PIN 35
  *AT91C_PIOC_ODR = (1<<3);
  *AT91C_PIOC_PPUDR = (1<<3);

  *AT91C_PIOC_PER = (1<<2);     //PIN 34
  *AT91C_PIOC_ODR = (1<<2);     //INPUT ENABLE REGISTER
  *AT91C_PIOC_PPUDR = (1<<2);    //Pull up disable register
 
  NVIC_ClearPendingIRQ(PIOD_IRQn);
 
  NVIC_SetPriority(PIOD_IRQn, 1);
   
  NVIC_EnableIRQ(PIOD_IRQn);
  
  *AT91C_PMC_PCER = (1<<36); // Activate PWM

  *AT91C_PMC_PCER = (1<<37); //Activate ADC
  
  *AT91C_PIOD_PER = (1 << 3);//Enables controll of the pin
  *AT91C_PIOD_OER = (1 << 3);//Enable pin output
  *AT91C_PIOD_PPUER = (1 << 3);//Enable Pull Up Register
}

int main()
{
  
  
        SystemInit(); 
        Config();
        init_Pins_Display();
        Init_Display();
        Clear_Display();  
        Init_clockTemp();
        
        record_Temperature();
        record_Temperature();
        record_Temperature();
        Clear_Display();  
        char array[10];
        sprintf(array, "%f", temperature);
        
        
        
        print_Text_Display(array, 0x0, 0x0);
        
        
        
        while(1);
  
        
  
  
  return 0;
}

