#include "at91sam3x8.h"
#include "system_sam3x.h"

#define AT91C_PIOD_AIMER (AT91_CAST(AT91_REG *) 0x400E14B0)
#define AT91C_PIOD_DIFSR (AT91_CAST(AT91_REG *) 0x400E1484)
#define AT91C_PIOD_SCDR (AT91_CAST(AT91_REG *) 0x400E148C)
#define AT91C_PWMC_CMRx (AT91_CAST(AT91_REG *)     0x4009422C) 


//#include "Temperature.h"
//#include "main.h"

void Config();
void Delay(int Value);
unsigned char Read_Status_Display(void);
void Write_Command_2_Display(unsigned char Command);
void Write_Data_2_Display(unsigned char Data);
void Init_Display(void);
void Clear_Display();
void Menu();
void set_DisplayAdress(char x, char y);
void print_Text_Display(char text[], char x, char y);

int status2 = 0, tdel=0,del=0; 
int flag_sevenDays = 0;                         // Flag for check of seven days gone.
int second = 0;
int minute = 0;

void init_Pins_Display()
{
  
  *AT91C_PMC_PCER = (3 << 13);  // Enable Clock ( C and D)
  *AT91C_PIOC_PER = 0x3BC;      // Enable PIOC 2 - 9
  *AT91C_PIOC_ODR = 0x3BC;      // Set pins as input
  *AT91C_PIOD_PER = (1<<2);
  *AT91C_PIOD_OER = (1<<2);
  *AT91C_PIOD_SODR = (1<<2);
  //display
  *AT91C_PMC_PCER = (3<<13);   
  *AT91C_PIOC_PER = (0xFF << 2);       
  *AT91C_PIOC_PER = (0xFF << 12);
  *AT91C_PIOC_ODR = (0xFF << 2); 
  *AT91C_PIOC_OER = (0xFF << 12);
  *AT91C_PIOC_SODR = (0x9 << 14);
  *AT91C_PIOC_SODR = (1 << 12);
  *AT91C_PIOC_PER  = 1;
  *AT91C_PIOC_OER  = 1;
}

void Delay(int Value)
{
  int i;
      for(i=0;i<Value;i++)
            asm("nop");
}
  
unsigned char Read_Status_Display(void)
{
  unsigned char Temp;
  
  *AT91C_PIOC_ODR = (255 << 2);
  *AT91C_PIOC_SODR = (1 << 13);
  *AT91C_PIOC_CODR = (1 << 12);
  *AT91C_PIOC_SODR = (1 << 14);
  *AT91C_PIOC_CODR = (1 << 15);
  *AT91C_PIOC_CODR = (1 << 16);
  Delay(25);
  Temp = (*AT91C_PIOC_PDSR >> 2);
  *AT91C_PIOC_SODR = (1 << 15);
  *AT91C_PIOC_SODR = (1 << 16);
  *AT91C_PIOC_SODR = (1 << 12);
  *AT91C_PIOC_CODR = (1 << 13);
  
  return Temp;
}

void Write_Command_2_Display(unsigned char Command)
{ 
  
  
  while(1){ 
    if((Read_Status_Display() & (3 << 0)) == (3 << 0)){     
      *AT91C_PIOC_CODR = (255 << 2);
      *AT91C_PIOC_SODR = (Command << 2);
      *AT91C_PIOC_CODR = (1 << 13);
      *AT91C_PIOC_CODR = (1 << 12);
      *AT91C_PIOC_OER = (255 << 2);
      *AT91C_PIOC_SODR = (1 << 14);
      *AT91C_PIOC_CODR = (1 << 15);
      *AT91C_PIOC_CODR = (1 << 17);
      Delay(25);
      *AT91C_PIOC_SODR = (1 << 15);
      *AT91C_PIOC_SODR = (1 << 17);
      *AT91C_PIOC_SODR = (1 << 12);
      *AT91C_PIOC_ODR = (255 << 2);
      break; 
    }
  }
}
void Write_Data_2_Display(unsigned char Data)
{

  while(1){
    if((Read_Status_Display() & (3 << 0)) == (3 << 0)){
      *AT91C_PIOC_CODR = (255 << 2);
      *AT91C_PIOC_SODR = (Data << 2);
      *AT91C_PIOC_CODR = (1 << 13);
      *AT91C_PIOC_CODR = (1 << 12);
      *AT91C_PIOC_OER = (255 << 2);
      *AT91C_PIOC_CODR = (1 << 14);
      *AT91C_PIOC_CODR = (1 << 15);
      *AT91C_PIOC_CODR = (1 << 17);
      Delay(25);
      *AT91C_PIOC_SODR = (1 << 15);
      *AT91C_PIOC_SODR = (1 << 17);
      *AT91C_PIOC_SODR = (1 << 12);
      *AT91C_PIOC_ODR = (255 << 2);
      break;
    }
  }
}

void Init_Display(void)
{ 
  
  *AT91C_PIOD_CODR = (1<<0);            //Make a Delay
  Delay(10);                            //Make a Delay
  *AT91C_PIOD_SODR = (1<<0);            //Make a Delay
 
 
  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x40);//Set text home address
  Write_Data_2_Display(0x00);
  Write_Data_2_Display(0x40);
  Write_Command_2_Display(0x42); //Set graphic home address
  Write_Data_2_Display(0x1e);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x41); // Set text area
  Write_Data_2_Display(0x1e);
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x43); // Set graphic area
  Write_Command_2_Display(0x80); // text mode
  Write_Command_2_Display(0x94); // Text on graphic o
}
void Clear_Display()
{
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x24);
 
  for (int i = 0; i < (16*40); i++){
    Write_Data_2_Display(0x00);
    Write_Command_2_Display(0xC0);
  }
  Write_Data_2_Display(0x00);
  Write_Command_2_Display(0x24);
}

void Menu()
{
  Clear_Display();
    
  print_Text_Display("Menu: ", 0x00, 0x00);
   
  print_Text_Display("1. Set Normal Mode", 0x1E, 0x00);
  print_Text_Display("2. Set Fast Mode", 0x3C, 0x00);
}

void set_DisplayAdress(char x, char y)
{    // Sets Address Pointer

  Write_Data_2_Display(x);
  Write_Data_2_Display(y);
  Write_Command_2_Display(0x24);
}

void print_Text_Display(char text[], char x, char y)
{
  int i = 0;
  
  set_DisplayAdress(x, y);

  while(i < strlen(text))               // Use != \0 // Where \0 means no character
  {
      Write_Data_2_Display(text[i]-0x20);
      Write_Command_2_Display(0xC0);
      i++;
  }  
}































