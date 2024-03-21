#include "at91sam3x8.h"
#include "system_sam3x.h"

void init_PWM ()        
{
  
    *AT91C_PMC_PCER = (1 << 12);  // Peripheral enable PIOB
    *AT91C_PMC_PCER1 = (1 << 4);  // Peripheral enable PWM

    *AT91C_PIOB_PDR = (1 << 17);    // Disable PDR (Enable peripheral)
    *AT91C_PIOB_ABMR = (1 << 17);   // Peripheral Select Register
    *AT91C_PWMC_ENA = (1 << 1);  // Enable PWM-channel for CHID1

    *AT91C_PWMC_CH1_CMR = 5;  // Set to Master_CLK/32

    // Set the period to 20ms
    *AT91C_PWMC_CH1_CPRDR = (int)(20.0 * 2625);
    // Set the cycle to 1ms     // 0 degrees
    *AT91C_PWMC_CH1_CDTYR = (int)(0.7 * 2625);
}

void turn_Servor(int key)   
{
  
  //int degrees = (2625.0 * (((1933 / 180) + key*10)));
  //int degrees = 2625.0 * ((((key * 10) * 1.933) / 180)+ 0.7);
  //float rotation = 2625.0 * (((1800 * 1933) / 180) + degrees);
  //*AT91C_PWMC_CH1_CDTYR = (unsigned int) rotation; 
  //*AT91C_PWMC_CH1_CDTYR = 2625.0 * (((180 * 1933) / 180) + degrees);
  (*AT91C_PWMC_CH1_CDTYR) = key; 
}