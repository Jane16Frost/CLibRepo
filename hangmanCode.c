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

// other system includes or your includes go here
//#include "pll.h"
//#include <stdlib.h>
//#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
// Local Prototypes
/////////////////////////////////////////////////////////////////////////////
void LoadGame(char* gameString);
int UpdateLetter(char currentLetter, char* gameString);
void ScrollLetters(char currentPosition, char* guessedLetters);
void DisplayLoseScreen(char* gameString);
void DisplayWinScreen(void);
void LoadCharacters(void);
void UpdateHangman(char currentState);
void ResetAlphaCharacters(char* alphaArray);
int CheckWin(char* gameString, char* guessedLetters);


/////////////////////////////////////////////////////////////////////////////
// Global Variables
/////////////////////////////////////////////////////////////////////////////
char currentScrollPosition = 0;
char alphaCharacters[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char hangmanWords[50][40] = {"Hello World!                            ",
                             "Error 404: Happinessnot found           ",
                             "Kirchoff's Voltage  Law                 ",
                             "As a game, I believein microtransactions",
                             "Money buys happiness(antidepressants)   ",
                             "Do you prefer a     nybble or byte?     ",
                             "To be or not to be, that is the question",
                             "What is my purpose?                     ",
                             "Code can't lie,     comments can.       ",
                             "Computer Processing Unit                ", 
                             "Computer EngineeringTechnology          ",
                             "Thank god it's      Friday              ",
                             "Girls just want to  have fun!           ",
                             "Marvel Cinematic    Universe            ",                             
                             "Red, Orange, Yellow,Green, Blue, Violet ",
                             "Have you tryed      turning it on?      ",
                             "When did you last   touch grass?        ",
                             "Cause I'm just a    teenage dirtbag     ",
                             "I hate when the codeworks the first time",
                             "Here's my ten cents,my two cents is free",
                             "Is my red the same  as your red?        ",
                             "It's not a bug it's a feature           ",
                             "Game Over!                              ",
                             "Are you even trying?                    ",
                             "There ain't no rest for the wicked      ",
                             "Dont wanna be an    American Idiot      ",
                             "Fix 1 bug, gain 100 more.               ",
                             "Random Access Memory                    ",
                             "What would happen   if a nuke just hit? ",
                             "Who brings a knife  to a gun fight?     ",
                             "Password, password, password!           ",
                             "Everything in       moderation          ",
                             "Potentiometer                           ",
                             "penguin                                 ",
                             "Klingon                                 ",
                             "Rheostat                                ",
                             "zigzagging                              ",
                             "alternating current                     ",
                             "Pascal's Wager                          ",
                             "Ship of Theseus                         ",
                             "Paradoxical                             ",
                             "pixel                                   ",
                             "knowledgable                            ",
                             "Cryptography                            ",
                             "Link Aggregration                       ",
                             "Network                                 ",
                             "differential                            ",
                             "Burgundy                                ",
                             "Rhythm Kitchen                          ",
                             "Asynchronus                             "};
                             
int userGuess = 'A';
int gameOn = 0;
int lives = 1;
unsigned long timer = 1;

unsigned int listPosition = 0;
char *currentWord;

SwState leftState = Idle;
SwState rightState = Idle;
SwState centerState = Idle;


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
  Clock_EnableOutput(0);
  LCD_Init();
  SWL_Init();
  LCD_8BitInit(LCD_Multiline, LCD_5x7);
  LCD_ON(LCD_Blink);
  
  LoadCharacters();
  /////////////////////////////////////////////////////////////////////////////
  // main program loop
  /////////////////////////////////////////////////////////////////////////////
  for (;;)
  {
    if(gameOn)
    {
      //Check if user is scrolling to desired letter
      if(leftState == Pressed && currentScrollPosition > 0)
      {
        ScrollLetters(--currentScrollPosition, &alphaCharacters[0]);      
      }
      if(rightState == Pressed && currentScrollPosition < 25)
      {
        ScrollLetters(++currentScrollPosition, &alphaCharacters[0]);
      }

      //Check if user is guessing a letter
      if(centerState == Pressed)
      {
        //If a valid letter left
        if(alphaCharacters[currentScrollPosition] != ' ')
        {
          //Save user guess and update display screen
          userGuess = alphaCharacters[currentScrollPosition];
          alphaCharacters[currentScrollPosition] = ' ';

          //If the letter is not found
          if(!UpdateLetter(userGuess, currentWord))
          {
            UpdateHangman(++lives);
          }

          //Update the user on their options
          ScrollLetters(currentScrollPosition, &alphaCharacters[0]);

          //Check if loose
          if(lives == 7)
          {
            DisplayLoseScreen(currentWord);
            gameOn = 0;
          }

          //Check if win
          if(!CheckWin(currentWord, &alphaCharacters[0]))
          {
            lives = 8;
            UpdateHangman(lives);
            DisplayWinScreen();
            gameOn = 0;
          }

        }
      }

    }
    else
    {
      
      //Reset Game
      if(centerState == Pressed)
      {

        //Bring Back all user choices
        ResetAlphaCharacters(&alphaCharacters[0]);
        
        //Generate the new string to guess
        listPosition = rand(srand(timer)) % 51;
        currentWord = &hangmanWords[listPosition][0];
        //Load the next guess
        LoadGame(currentWord);
        
        //Reset Life counter
        lives = 1;
        UpdateHangman(lives);
        
        currentScrollPosition = 0;
        ScrollLetters(currentScrollPosition, &alphaCharacters[0]);
        
        //Set Game True
        gameOn = 1;
      }
    }

    Sw_Process(&leftState, SWL_LEFT);
    Sw_Process(&rightState, SWL_RIGHT);
    Sw_Process(&centerState, SWL_CTR);
    timer++;
  }
  
}

/////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////
void LoadGame(char* gameString)
{
  int length = 20;

  LCD_SetDDRamAddress(0x00);
  for(length = 0; length < 20; length++)
  {
    if((*gameString >= 'A' && *gameString <= 'Z')
      ||*gameString >= 'a' && *gameString <= 'z')
    {
      LCD_WriteCharacterToDisplay('_');
    }
    else
    {
      LCD_WriteCharacterToDisplay(*gameString);
    }
    gameString++;
  }

  LCD_SetDDRamAddress(0x40);
  for(length = 0; length < 20; length++)
  {
    if((*gameString >= 'A' && *gameString <= 'Z')
      ||*gameString >= 'a' && *gameString <= 'z')
    {
      LCD_WriteCharacterToDisplay('_');
    }
    else
    {
      LCD_WriteCharacterToDisplay(*gameString);
    }
    gameString++;
  }

}

int UpdateLetter(char currentLetter, char* gameString)
{
  int length = 20;
  int letterSwitched = 0;
  
  LCD_SetDDRamAddress(0x00);
  for(length = 0; length < 20; length++)
  {
    if(*gameString == currentLetter || *gameString == currentLetter + 32)
    {
      LCD_WriteCharacterToDisplay(*gameString);
      letterSwitched++;
    }
    else
    {
      LCD_MoveCursor(LCD_ShiftCursor, LCD_DirectionRight);
    }
    gameString++;
  }

  LCD_SetDDRamAddress(0x28);
  for(length = 0; length < 20; length++)
  {
    if(*gameString == currentLetter || *gameString == currentLetter + 32)
    {
      LCD_WriteCharacterToDisplay(*(gameString));
      letterSwitched++;
    }
    else
    {
      LCD_MoveCursor(LCD_ShiftCursor, LCD_DirectionRight);
    }
    gameString++;
  }
  
  return letterSwitched;

}

void ScrollLetters(char currentPosition, char* guessedLetters)
{
  int screenLength = 0;
  LCD_SetDDRamAddress(0x59);
  
  for(screenLength = -5; screenLength < 6; screenLength++)
  {
    if(screenLength + currentPosition >= 0 && screenLength+currentPosition <= 25)
    {
      LCD_WriteToDisplay(guessedLetters, screenLength + currentPosition);

    }
    else 
    {
      LCD_WriteCharacterToDisplay(' ');
    }

  }

  LCD_SetDDRamAddress(0x5E);
}

void DisplayLoseScreen(char* gameString)
{
  int length = 0;
  char gameOver[] = " Game Over!";

  LCD_SetDDRamAddress(0x00);
  for(length = 0; length < 20; length++)
  {

      LCD_WriteCharacterToDisplay(*gameString);
    

    gameString++;
  }

  LCD_SetDDRamAddress(0x40);
  for(length = 0; length < 20; length++)
  {

      LCD_WriteCharacterToDisplay(*gameString);
    
    gameString++;
  }
  LCD_SetDDRamAddress(0x59);
  for(length = 0; length < 11; length++)
  {
    LCD_WriteToDisplay(&gameOver[0], length);
  }

}
void DisplayWinScreen(void)
{
  int screenLength = 0;
  char win[] = "  Winner!  ";
  LCD_SetDDRamAddress(0x59);
  
  for(screenLength = 0; screenLength < 11; screenLength++)
  {
    LCD_WriteToDisplay(&win[0], screenLength);
  }

}

void LoadCharacters(void)
{
  char character[7] = {0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  
  LCD_SetCGRamAddress(1);
  LCD_WriteCharacterType(character, LCD_5x7);

  character[0] = 0x0E;
  character[1] = 0x0E;
  character[2] = 0x04;
  LCD_SetCGRamAddress(2);
  LCD_WriteCharacterType(character, LCD_5x7);

  character[3] = 0x04;
  character[4] = 0x04;
  LCD_SetCGRamAddress(3);
  LCD_WriteCharacterType(character, LCD_5x7);

  character[3] = 0x1C;
  LCD_SetCGRamAddress(4);
  LCD_WriteCharacterType(character, LCD_5x7);

  character[3] = 0x1F;  
  LCD_SetCGRamAddress(5);
  LCD_WriteCharacterType(character, LCD_5x7);

  character[5] = 0x08;
  character[6] = 0x08;
  LCD_SetCGRamAddress(6);
  LCD_WriteCharacterType(character, LCD_5x7);

  character[5] = 0x0A;
  character[6] = 0x0A;
  LCD_SetCGRamAddress(7);  
  LCD_WriteCharacterType(character, LCD_5x7);

  character[0] = 0x1f;
  character[2] = 0x15;
  character[3] = 0x0E;
  character[5] = 0x04;
  character[6] = 0x0E;
  LCD_SetCGRamAddress(8);
  LCD_WriteCharacterType(character, LCD_5x7);

}

void UpdateHangman(char currentState)
{
  LCD_SetDDRamAddress(0x54);
  LCD_WriteCharacterToDisplay(currentState);
}

void ResetAlphaCharacters(char* alphaArray)
{
  unsigned char stringLength = 0;

  for (stringLength = 0; stringLength < 26; stringLength++)
  {
    *alphaArray++ = ('A' + stringLength);
  }
  
}

int CheckWin(char *gameString, char* guessedLetters)
{
  int currentLetter = 0;
  int lettersLeft = 0;
  for(currentLetter = 0; currentLetter < 40; currentLetter++)
  {
    if(*gameString >= 'A' && *gameString <= 'Z')
    {
      if(*(guessedLetters + *gameString - 'A') != ' ')
      {
        lettersLeft++;
      }
    }
    else if(*gameString >= 'a' && *gameString <= 'z')
    {
      if(*(guessedLetters + *gameString - 'a') != ' ')
      {
        lettersLeft++;
      }
    }

    gameString++;
  }
  return lettersLeft;
}

/////////////////////////////////////////////////////////////////////////////
// Interrupt Service Routines
/////////////////////////////////////////////////////////////////////////////
