#include "at91sam3x8.h"
#include "system_sam3x.h"

int status = 0;

void init_Systick()
{
  
  SysTick_Config(SystemCoreClock/1000);         //Interrupt **Every Millisecond
}

void SysTick_Handler()          // Do Not Operate Here To Much
{
  
  status ++;
}  