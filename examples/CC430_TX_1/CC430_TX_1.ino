#include <ez430chronoslib.h>
#include <OPEN_RF.h>
#include <SPI.h>


byte str[] ={1,2,3,4,5,6,7,8,9,10}; 


void setup()
{
  
  lcd_init();
  
  OPEN_rf.Init(); 
  
  OPEN_rf.SetModulation(MODULATION_ASK_OOK);
  OPEN_rf.EnableAdressCheck(TRUE);
  OPEN_rf.EnableCRC(FALSE);
    
  clear_line(LINE1);
  clear_line(LINE2);
     
 }

void loop() {
  
  
  display_symbol(LCD_ICON_HEART ,SEG_ON);
  
  OPEN_rf.SendDataTo(23,str,9); // send 9 byte of str to address 23
  
  delay(1000);
  
   display_symbol(LCD_ICON_HEART ,SEG_OFF);
    
   OPEN_rf.SendDataTo(23,str,9);
  
  delay(1000);
  
}
