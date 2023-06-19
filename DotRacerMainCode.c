/////////////////////////////////////////////////////////////////////////////
// 9S12X Program: Working HExDisplay and Library
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz (Requires Active PLL)
// Author:        Jai-lea Franson
// Details:       A more detailed explanation of the program is entered here
// Date:          02/23/2022

/////////////////////////////////////////////////////////////////////////////
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "sw_led.h"
#include "lcd.h"
#include "clock.h"
#include "hexDisplay.h"
// other system includes or your includes go here
//#include "pll.h"
//#include <stdlib.h>
//#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
// Local Prototypes
/////////////////////////////////////////////////////////////////////////////
void LoadMap (char* mapAdd);
void LoadCharacters(void);
void DrawScreen(char*, char);
void UpdatePlayerIcon(char* characterMap, char player);
void SpawnMapEdge(char* gridMap, int currentCycle);
void DisplayLoseScreen(void);

/////////////////////////////////////////////////////////////////////////////
// Global Variables
/////////////////////////////////////////////////////////////////////////////
unsigned long timer = 0;
int gameOn = 0;
char playerPosition = 3;
int updateDelay = 10000;
char map[8][20];
int score = -15;
char scoreDigits[4];

SwState upState = Idle;
SwState downState = Idle;
SwState ctrState = Idle;

/////////////////////////////////////////////////////////////////////////////
//          Constants
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//          Main Entry
/////////////////////////////////////////////////////////////////////////////
void main(void)
{
  // main entry point - these two lines must appear first
  _DISABLE_COP();
  EnableInterrupts;
  
  /////////////////////////////////////////////////////////////////////////////
  // one-time initializations
  /////////////////////////////////////////////////////////////////////////////
  Clock_Set8MHZ();
  LCD_Init();
  HEX_Init();
  SWL_Init();
  LCD_8BitInit(LCD_Multiline, LCD_5x7);
  LCD_ON(LCD_NoCursor);
  
  LoadCharacters();
  /////////////////////////////////////////////////////////////////////////////
  // main program loop
  /////////////////////////////////////////////////////////////////////////////
  for (;;)
  {
    if(gameOn)
    { //Run Game play
      if(upState == Pressed && playerPosition > 1)
      {
        playerPosition--;
        DrawScreen(&map[0], playerPosition);
        UpdatePlayerIcon(&map[0], playerPosition);
      }
      if(downState == Pressed && playerPosition < 6)
      {
        playerPosition++;
        DrawScreen(&map[0], playerPosition);
        UpdatePlayerIcon(&map[0], playerPosition);
      }

      if(!(timer % updateDelay))
      {
        SpawnMapEdge(&map[0], score);
        DrawScreen(&map[0], playerPosition);
        if (updateDelay)
        {
          updateDelay-= 10;
        }
        
        score++;
        if(score > 0)
        {
          HEX_DigitConverter(score, &scoreDigits);
        }
        else
        {
          scoreDigits[0] = 0;
          scoreDigits[1] = 0;
          scoreDigits[2] = 0;
          scoreDigits[3] = 0;

        }
        HEX_DisplayRedBCode(&scoreDigits);

        if(map[playerPosition][2] == 1)
        {
          gameOn = 0;
          DisplayLoseScreen();
        }
      } 
  
    }
    else
    {
      if(ctrState == Pressed)
      {
        //Reset Game
        LoadMap(&map[0]);
        playerPosition = 3;
        DrawScreen(&map[0], playerPosition);
        score = -15;
        gameOn = 1;
      }

    }

    Sw_Process(&upState, SWL_UP);
    Sw_Process(&downState, SWL_DOWN);
    Sw_Process(&ctrState, SWL_CTR);
    timer++;
  }  
  
}

/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////
void LoadMap (char* mapAdd)
{
  int length;
  for(length = 0; length < 20; length++)
  {
    *mapAdd++ = 1;
  }
  for(length = 0; length < 120; length++)
  {
    *mapAdd++ = 0;
  }
  for(length = 0; length < 20; length++)
  {
    *mapAdd++ = 1;
  }

}

void LoadCharacters(void)
{
  char character[7] = {0x04, 0x0E, 0x04, 0x00, 0x00, 0x00, 0x00};
  
  LCD_SetCGRamAddress(1);
  LCD_WriteCharacterType(character, LCD_5x7);

  character[4] = 0x1F;
  character[5] = 0x1F;
  character[6] = 0x1F;
  LCD_SetCGRamAddress(2);
  LCD_WriteCharacterType(character, LCD_5x7);

  character[0] = 0x00;
  character[1] = 0x00;
  character[2] = 0x00;
  LCD_SetCGRamAddress(3);
  LCD_WriteCharacterType(character, LCD_5x7);

  character[0] = 0x1F;
  character[1] = 0x1F;
  character[2] = 0x1F;
  character[4] = 0x00;
  character[5] = 0x00;
  character[6] = 0x00;
  LCD_SetCGRamAddress(4);
  LCD_WriteCharacterType(character, LCD_5x7);

  character[4] = 0x04;
  character[5] = 0x0E;  
  character[6] = 0x04;  
  LCD_SetCGRamAddress(5);
  LCD_WriteCharacterType(character, LCD_5x7);

  character[0] = 0x00;
  character[1] = 0x00;
  character[2] = 0x00;
  LCD_SetCGRamAddress(6);
  LCD_WriteCharacterType(character, LCD_5x7);

}

void DrawScreen(char* characterMap, char player)
{
  int length;
  LCD_SetDDRamAddress(0x00);
  for(length = 0; length < 20; length++)
  {
    if(*(characterMap + 20))
    {
      //Top Solid, Bottom Solid
      LCD_WriteCharacterToDisplay(0xFF);
    }
    else
    {
      //Top Solid, Bottom Empty
      LCD_WriteCharacterToDisplay(4);
    }
    characterMap++;
  }
  characterMap+= 20;

  LCD_SetDDRamAddress(0x40);
  for(length = 0; length < 20; length++)
  {
    if(*characterMap)
    { //Top Solid
      if(*(characterMap + 20))
      { //Bottom Solid
        LCD_WriteCharacterToDisplay(0xFF);
      }
      else
      { //Bottom Open
        LCD_WriteCharacterToDisplay(4);
      }
    }
    else
    { //Top Open
      if(*(characterMap + 20))
      { //Bottom Solid
        LCD_WriteCharacterToDisplay(3);
      }
      else
      { //Bottom Open
        LCD_WriteCharacterToDisplay(' ');
      }
    }
    characterMap++;
  }
  characterMap+= 20;

  LCD_SetDDRamAddress(0x14);
  for(length = 0; length < 20; length++)
  {
    if(*characterMap)
    { //Top Solid
      if(*(characterMap + 20))
      { //Bottom Solid
        LCD_WriteCharacterToDisplay(0xFF);
      }
      else
      { //Bottom Open
        LCD_WriteCharacterToDisplay(4);
      }
    }
    else
    { //Top Open
      if(*(characterMap + 20))
      { //Bottom Solid
        LCD_WriteCharacterToDisplay(3);
      }
      else
      { //Bottom Open
        LCD_WriteCharacterToDisplay(' ');
      }
    }
    characterMap++;
  }
  characterMap+= 20;

  LCD_SetDDRamAddress(0x54);
  for(length = 0; length < 20; length++)
  {
    if(*(characterMap))
    {
      //Top Solid, Bottom Solid
      LCD_WriteCharacterToDisplay(0xff);
    }
    else
    {
      //Top Empty, Bottom Solid
      LCD_WriteCharacterToDisplay(3);
    }
    characterMap++;
  }
  
  characterMap -= 140;

  switch(player)
  {
    case 1:
    LCD_SetDDRamAddress(0x02);
    LCD_WriteCharacterToDisplay(5);
    break;

    case 2:
    LCD_SetDDRamAddress(0x42);
    //Player top
    if(*(characterMap + 62))
    { //Solid Bottom
      LCD_WriteCharacterToDisplay(2);
    }
    else
    { //open Bottom
      LCD_WriteCharacterToDisplay(1);
    }
    break;
    
    case 3:
    LCD_SetDDRamAddress(0x42);
    //Player Bottom
    if(*(characterMap + 42))
    { //Solid Top
      LCD_WriteCharacterToDisplay(5);
    }
    else
    { //Open top
      LCD_WriteCharacterToDisplay(6);
    }
    break;
    
    case 4:
    LCD_SetDDRamAddress(0x16);

    //Player Top
    if(*(characterMap + 102))
    { //Solid Bottom
      LCD_WriteCharacterToDisplay(2);
    }
    else
    { //open Bottom
      LCD_WriteCharacterToDisplay(1);
    }
    break;
  
    case 5:
    LCD_SetDDRamAddress(0x16);
    // //Player Bottom
    if(*(characterMap + 82))
    { //Solid Top
      LCD_WriteCharacterToDisplay(5);
    }
    else
    { //Open top
      LCD_WriteCharacterToDisplay(6);
    }
    break;

    case 6:
    LCD_SetDDRamAddress(0x56);
    LCD_WriteCharacterToDisplay(2);
    break;
  }

}

void UpdatePlayerIcon(char* characterMap, char player)
{
    switch(player)
  {
    case 1:
    LCD_SetDDRamAddress(0x02);
    break;

    case 2:
    LCD_SetDDRamAddress(0x42);
    break;
    
    case 3:
    LCD_SetDDRamAddress(0x42);
    break;
    
    case 4:
    LCD_SetDDRamAddress(0x16);
    break;
  
    case 5:
    LCD_SetDDRamAddress(0x16);
    break;

    case 6:
    LCD_SetDDRamAddress(0x56);
    break;
  }
}

void SpawnMapEdge(char* gridMap, int currentCycle)
{
  int length;
  char generatedValues[6] = {0,0,0,0,0,0};
  int random = srand(timer);
  if(currentCycle % 3 == 0)
  {
    generatedValues[rand(random) % 6] = 1;
    generatedValues[rand(random) % 6] = 1;
    generatedValues[rand(random) % 6] = 1;

  }
//  generatedValues[rand(random) % 6] = 1;

  gridMap+= 20;
  for(length = 0; length < 19; length++)
  {
    *gridMap = *(gridMap + 1);
    gridMap++;
  }
  *gridMap++ = generatedValues[0];

  for(length = 0; length < 19; length++)
  {
    *gridMap = *(gridMap + 1);
    gridMap++;
  }
  *gridMap++ = generatedValues[1];
  
  for(length = 0; length < 19; length++)
  {
    *gridMap = *(gridMap + 1);
    gridMap++;
  }
  *gridMap++ = generatedValues[2];

  for(length = 0; length < 19; length++)
  {
    *gridMap = *(gridMap + 1);
    gridMap++;
  }
  *gridMap++ = generatedValues[3];

  for(length = 0; length < 19; length++)
  {
    *gridMap = *(gridMap + 1);
    gridMap++;
  }
  *gridMap++ = generatedValues[4];

  for(length = 0; length < 19; length++)
  {
    *gridMap = *(gridMap + 1);
    gridMap++;
  }
  *gridMap++ = generatedValues[5];

}

void DisplayLoseScreen(void)
{
  int length = 0;
  char gameOver[] = " Game Over!";

  LCD_SetDDRamAddress(0x2D);
  for(length = 0; length < 11; length++)
  {
    LCD_WriteToDisplay(&gameOver[0], length);
  }

}

/////////////////////////////////////////////////////////////////////////////
// Interrupt Service Routines
/////////////////////////////////////////////////////////////////////////////



