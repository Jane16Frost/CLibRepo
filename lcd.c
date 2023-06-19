#include "derivative.h"
#include "lcd.h"


///////////////////////////////////////////////////////
//        Initalization Functions
///////////////////////////////////////////////////////

void LCD_Init(void)
{
    unsigned long delay = 2000;
    
    DDRH = 0xff;
    RDRH = 0x00;
    DDRK |= 0x07;


    while(delay--);//Wait 16mS
    PTH = 0x30;
    PORTK = 0x01;
    lcd_MicroDelay;
    PORTK = 0x00;
 
    delay = 1000;
    while(delay--); //Wait 8mS
    PORTK = 0x01;
    lcd_MicroDelay;
    PORTK = 0x00;

    delay = 100; //wait 8uS
    while(delay--);
}

void LCD_8BitInit(char lines, char size)
{
  WaitForBusyFlag();
  PORTK = 0x01;
    lcd_MicroDelay;

  PORTK = 0x00;


  ///////////////////////////////////////////
  //    Function Set - 1 line // 5x7 dots
  ///////////////////////////////////////////
  WaitForBusyFlag();
  lines |= size;
  lines |= 0x30;
  PTH = lines;
  PORTK = 0x01;
    lcd_MicroDelay;

  PORTK = 0x00;


  ////////////////////////////////////////////
  //            Display Off
  ////////////////////////////////////////////
    WaitForBusyFlag();
    PTH = 0x08;
    PORTK = 0x01;
    lcd_MicroDelay;

    PORTK = 0x00;


  ////////////////////////////////////////////
  //          Clear Display
  ////////////////////////////////////////////
  WaitForBusyFlag();
  PTH = 0x01;
  PORTK = 0x01;
    lcd_MicroDelay;

  PORTK = 0x00;

}

void LCD_SetEntryMode(char incStyle, char cursorStyle)
{
    WaitForBusyFlag();
    PTH = incStyle;
    PORTK = 0x01;
    lcd_MicroDelay;

    PORTK = 0x00;


  ////////////////////////////////////////////////
  //            Display On
  ////////////////////////////////////////////////
  WaitForBusyFlag();
  PTH = cursorStyle;
  PORTK = 0x01;
    lcd_MicroDelay;

  PORTK = 0x00;

}

void LCD_ON(char cursorStyle)
{
  WaitForBusyFlag();
  ////////////////////////////////////////////////
  //            Display On
  ////////////////////////////////////////////////
  PTH = cursorStyle;
  PORTK = 0x01;
    lcd_MicroDelay;

  PORTK = 0x00;

}

void LCD_OFF(void)
{
    WaitForBusyFlag();
    
    PTH = 0x08;
    PORTK = 0x01;
    lcd_MicroDelay;

    PORTK = 0x00;
}

///////////////////////////////////////////////////////
//          Busy Flag Functions
//////////////////////////////////////////////////////
void WaitForBusyFlag(void)
{
  unsigned long delay = 1;  
    //Read Busy Flag
    DDRH = 0x00; //Enable busy flag as output
    lcd_MicroDelay;

    PORTK = 0x03;

    while(delay--);

    while(PTH & 0x80);
    //Wait for no busy Flag

    //Clear Read busy Flag
    PORTK = 0x00;
    lcd_MicroDelay;

    DDRH = 0xFF;

}

char CheckBusyFlag(void)
{
        //Read Busy Flag
    DDRH = 0x00; //Enable busy flag as output
    PORTK = 0x03;

    if(PTH & 0x80)
    {
        //Clear Read busy Flag
        PORTK = 0x00;
        DDRH = 0xFF;
        return 0;
    }
    else
    {
        //Clear Read busy Flag
        PORTK = 0x00;
        DDRH = 0xFF;

        return 1;
    }
    //Wait for no busy Flag


}

char CheckAddress(void)
{
    DDRH = 0x00; //Enable busy flag as output
    PORTK = 0x03;
    lcd_MicroDelay;
    
    //Clear Read busy Flag
    PORTK = 0x00;
    DDRH = 0xFF;
     
    return PTH;
}

//////////////////////////////////////////////////////
//          Write to Display Functions
////////////////////////////////////////////////////
void LCD_WriteToDisplay(unsigned char* message, char position)
{ 
    WaitForBusyFlag();
    
    PTH = *(message + position);
    PORTK = 0x05;
    lcd_MicroDelay;

    PORTK = 0x00;

}
void LCD_WriteCharacterToDisplay(unsigned char character)
{

    WaitForBusyFlag();
    PTH = character;
    PORTK = 0x05;
    lcd_MicroDelay;

    PORTK = 0x00;

}

void LCD_WriteStringToDisplay(unsigned char * character)
{   
    int loopCounter = 0;

    while (loopCounter < 80 && *character != '\0')
    {
        LCD_WriteCharacterToDisplay(*character);
        loopCounter++; character++;
    }
    

}

void LCD_ClearScreen(void)
{
    WaitForBusyFlag();
    
    PTH = 0x01;
    PORTK = 0x01;
    lcd_MicroDelay;
    PORTK = 0x00;

}

//////////////////////////////////////////////////////
//      Create Character Functions
//////////////////////////////////////////////////////
void LCD_WriteCharacterType(char image[], char size)
{
    char loop;

    if(size == LCD_5x7)
    {
        for ( loop = 0; loop < 7; loop++)
        {
            WaitForBusyFlag();
            
            PTH = image[loop];
            PORTK = 0x05;
    lcd_MicroDelay;

            PORTK = 0x00;

        }
        WaitForBusyFlag();
            
            PTH = 0x00;
            PORTK = 0x05;
    lcd_MicroDelay;

            PORTK = 0x00;
    }
    else
    {
        for ( loop = 0; loop < 10; loop++)
        {
            PTH = image[loop];
            PORTK = 0x05;
    lcd_MicroDelay;

            PORTK = 0x00;

            WaitForBusyFlag();
        }
        
    }
    

}

//////////////////////////////////////////////////////
//         Manipulate Cursour Functions
//////////////////////////////////////////////////////
void LCD_ReturnHome(void)
{
    WaitForBusyFlag();
    
    PTH = 0x03;
    PORTK = 0x01;
    lcd_MicroDelay;
    PORTK = 0x00;

}

void LCD_SetCGRamAddress(char address)
{
    address <<= 3;
    address |= 0x40;
    address  &= ~0x87;
    
    WaitForBusyFlag();

    PTH = address;
    PORTK = 0x01;
    lcd_MicroDelay;
    PORTK = 0x00;

}

void LCD_SetDDRamAddress(char address)
{
    WaitForBusyFlag();
    
    address |= 0x80;
    PTH = address;
    PORTK = 0x01;
    lcd_MicroDelay;
    PORTK = 0x00;

}

void lcd_AddrXY (unsigned char ix, unsigned char iy)
{
    char position;
    switch (iy)
  {
  case 0:
    position = ix;
    break;
  case 1:
    position = 64 + ix;
    break;
  case 2:
    position = 20 + ix;
    break;
  default:
    position = 84+ix;
    break;
  }
  LCD_SetDDRamAddress(position);
}

void LCD_MoveCursor(char movementType, char direction)
{
    WaitForBusyFlag();
    
    movementType |= direction;
    movementType |= 0x10;

    PTH = movementType;
    PORTK = 0x01;
    lcd_MicroDelay;
    PORTK = 0x00;
}