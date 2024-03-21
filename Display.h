// external interfaces for display.c 
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
