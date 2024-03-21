#include "at91sam3x8.h"
#include "system_sam3x.h"
#include <stdio.h>
#include <stdlib.h>

#include "Keypad.h"

#include "Display.h"

int pressed_Key(void);
char hexa_Key(int key);
void write_Key_Display(int key);
void write_Number (char key);
float char_floatValue();

int pressed_Key(void)
{
  int value = 0;

  //Clear OE KEY BUS (Active Low)   
  *AT91C_PIOD_CODR = (1<<2);         //PIN 27

  //Make all Column pin as output
  *AT91C_PIOC_OER = (1<<7);   // (PIOC) PIO Enable Register PIN 39

  //PIN 40
  *AT91C_PIOC_OER = (1<<8);
  
  //PIN 41
  *AT91C_PIOC_OER = (1<<9);

  //Set all Column pin as high
  // (PIOC) PIO Enable Register PIN 39
  *AT91C_PIOC_SODR = (1<<7);
  
  //PIN 40
  *AT91C_PIOC_SODR = (1<<8);
  
  //PIN 41
  *AT91C_PIOC_SODR = (1<<9);

  //Loop Column
  
  //Clear one column at the time
    for (int i = 0; i < 3;i++){
      *AT91C_PIOC_CODR = (1<<9-i);     
            //Loop Row
            //Read row and check if bit is zero

       for(int j = 0; j < 4; j++){
            if((*AT91C_PIOC_PDSR & (1<<5-j)) == 0)
                  value = (j*3)+i+1;
       }
    *AT91C_PIOC_SODR = (1<<7);
    *AT91C_PIOC_SODR = (1<<8);
    *AT91C_PIOC_SODR = (1<<9);
    }    
  //End loop Column

  
  //Make all Column pin as input
  *AT91C_PIOC_ODR = (1<<7);
  *AT91C_PIOC_ODR = (1<<8);
  *AT91C_PIOC_ODR = (1<<9);
  
  
  return value;
}

char hexa_Key(int key) //return hexa value
{        
    
    if(key == 1)       {
      return 0x11;
    }
    if (key == 2)       {
      return 0x12;
    }
    if (key == 3)       {
      return 0x13;
    }
    if (key == 4)       {
      return 0x14;
    }
    if (key == 5)       {
      return 0x15;
    }
    if (key == 6)       {
      return 0x16;
    }
    if (key == 7)       {
      return 0x17;
    }
    if (key == 8)       {
      return 0x18;
    }
    if (key == 9)       {
      return 0x19;
    }
    if (key == 10)      {
      return 0x0A;
    }
    if (key == 11)      {
      return 0x10;
    }
    if (key == 12)      {
      return 0x03;
    }
  
}  

void write_Key_Display(int key)       
{

  write_Number(hexa_Key(key));  
}

void write_Number (char key) 
{
  

 
  Write_Data_2_Display(key);
  Write_Command_2_Display(0xC0);
}

float char_floatValue()
{
    
    char c[10]={0};
    int i = 0;
    int prevkey;
    int key = -1;
    while(key != 12)
    {   
      key = pressed_Key();
      while (pressed_Key() == key);   
      printf("%i", key);
      if (key == 10 && key != 12)
      {
        c[i] = '.';
        prevkey = key;
      }
      if(key != -1 && key != 10 && key != 11 && key != 12)
      {
         c[i] = key + '0';

         i++;
         prevkey = key;
      }
      if (key == 11 && key != 12)
      {
        c[i] = 0 +'0';

        i++;
        prevkey = key;
      }
      
      if (key == 10 && key!= 12)
      {
        
        c[i] = '.';
        i++;
      }
        
    }
    
    c[i] = '\0';
    
    // Add '0' to Convert an int to char.
    
    return atof(c) ;
}












