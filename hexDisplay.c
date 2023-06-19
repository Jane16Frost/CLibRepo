#include "derivative.h"
#include "hexDisplay.h"

void HEX_Init(void){
    DDRA |= 0x03;
    DDRB = 0xFF;
}

void HEX_Off(void){
    PORTB = DISABLE_DISPLAY;
    PORTA = 0x02;
    PORTA = 0x03;
}

///////////////////////////////////////////////////////////////
// Display Variable on Hex functions

void HEX_SendAllHexCode(char digitRed1, char digitRed2, char digitRed3, char digitRed4, char digitOrange1, char digitOrange2, char digitOrange3, char digitOrange4)
{  
            PORTB = ENABLE_HEX_MultiSend;
            PORTA = 0x02;
            PORTA = 0x03;

            PORTB = digitRed1;
            PORTA = 0x00;
            PORTA = 0x01;
            
            PORTB = digitRed2;
            PORTA = 0x00;
            PORTA = 0x01;
            PORTB = digitRed3;
            PORTA = 0x00;
            PORTA = 0x01;
            
            PORTB = digitRed4;
            PORTA = 0x00;
            PORTA = 0x01;

            PORTB = digitOrange1;
            PORTA = 0x00;
            PORTA = 0x01;
            
            PORTB = digitOrange2;
            PORTA = 0x00;
            PORTA = 0x01;

            PORTB = digitOrange3;
            PORTA = 0x00;
            PORTA = 0x01;
            
            PORTB = digitOrange4;
            PORTA = 0x00;
            PORTA = 0x01;
}
void HEX_DisplayAllHexCode(char redDigits[], char orangeDigits[])
{
            char loop = 0;

            PORTB = ENABLE_HEX_MultiSend;
            PORTA = 0x02;
            PORTA = 0x03;

            for(loop = 0; loop < 4; loop++)
            {
                redDigits[loop] |= 0x80;
                PORTB = redDigits[loop];
                PORTA = 0x00;
                PORTA = 0x01;
            }

            for(loop = 0; loop < 4; loop ++)
            {
                orangeDigits[loop] |= 0x80;
                PORTB = orangeDigits[loop];
                PORTA = 0x00;
                PORTA = 0x01;
            }
}

void HEX_SendRedBCode(char digitRed1, char digitRed2, char digitRed3, char digitRed4)
{
            char loop = 0;

            PORTB = ENABLE_BCODE_MultiSend;
            PORTA = 0x02;
            PORTA = 0x03;

            PORTB = digitRed1;
            PORTA = 0x00;
            PORTA = 0x01;
            
            PORTB = digitRed2;
            PORTA = 0x00;
            PORTA = 0x01;
            PORTB = digitRed3;
            PORTA = 0x00;
            PORTA = 0x01;
            
            PORTB = digitRed4;
            PORTA = 0x00;
            PORTA = 0x01;

            for(loop = 0; loop < 4; loop ++)
            {
                PORTB = BCODE_BLANK;
                PORTA = 0x00;
                PORTA = 0x01;
            }

}
void HEX_DisplayRedBCode(char digits[])
{
                char loop = 0;

            PORTB = ENABLE_BCODE_MultiSend;
            PORTA = 0x02;
            PORTA = 0x03;

            for(loop = 0; loop < 4; loop++)
            {
                digits[loop] |= 0x80;
                PORTB = digits[loop];
                PORTA = 0x00;
                PORTA = 0x01;
            }

            for(loop = 0; loop < 4; loop ++)
            {
                PORTB = BCODE_BLANK;
                PORTA = 0x00;
                PORTA = 0x01;
            }
}

void HEX_SendOrangeBCode(char digitOragne1, char digitOrange2, char digitOrange3, char digitOrange4)
{        
            char loop = 0;
            
            PORTB = ENABLE_BCODE_MultiSend;
            PORTA = 0x02;
            PORTA = 0x03;
            
            for(loop = 0; loop < 4; loop ++)
            {
                PORTB = BCODE_BLANK;
                PORTA = 0x00;
                PORTA = 0x01;
            }

            PORTB = digitOragne1;
            PORTA = 0x00;
            PORTA = 0x01;
            
            PORTB = digitOrange2;
            PORTA = 0x00;
            PORTA = 0x01;

            PORTB = digitOrange3;
            PORTA = 0x00;
            PORTA = 0x01;
            
            PORTB = digitOrange4;
            PORTA = 0x00;
            PORTA = 0x01;

}
void HEX_DisplayOrangeBCode(char digits[])
{
            char loop = 0;

            PORTB = ENABLE_BCODE_MultiSend;
            PORTA = 0x02;
            PORTA = 0x03;

            for(loop = 0; loop < 4; loop ++)
            {
                PORTB = BCODE_BLANK;
                PORTA = 0x00;
                PORTA = 0x01;
            }
            for(loop = 0; loop < 4; loop++)
            {
                digits[loop] |= 0x80;
                PORTB = digits[loop];
                PORTA = 0x00;
                PORTA = 0x01;
            }

}

void HEX_SendAllBCode(char digitRed1, char digitRed2, char digitRed3, char digitRed4, char digitOrange1, char digitOrange2, char digitOrange3, char digitOrange4)
{
            PORTB = ENABLE_BCODE_MultiSend;
            PORTA = 0x02;
            PORTA = 0x03;

            PORTB = digitRed1;
            PORTA = 0x00;
            PORTA = 0x01;
            
            PORTB = digitRed2;
            PORTA = 0x00;
            PORTA = 0x01;
            PORTB = digitRed3;
            PORTA = 0x00;
            PORTA = 0x01;
            
            PORTB = digitRed4;
            PORTA = 0x00;
            PORTA = 0x01;

            PORTB = digitOrange1;
            PORTA = 0x00;
            PORTA = 0x01;
            
            PORTB = digitOrange2;
            PORTA = 0x00;
            PORTA = 0x01;

            PORTB = digitOrange3;
            PORTA = 0x00;
            PORTA = 0x01;
            
            PORTB = digitOrange4;
            PORTA = 0x00;
            PORTA = 0x01;
}
void HEX_DisplayAllBCode(char redDigits[], char orangeDigits[])
{
            char loop = 0;

            PORTB = ENABLE_BCODE_MultiSend;
            PORTA = 0x02;
            PORTA = 0x03;

            for(loop = 0; loop < 4; loop++)
            {
                redDigits[loop] |= 0x80;
                PORTB = redDigits[loop];
                PORTA = 0x00;
                PORTA = 0x01;
            }

            for(loop = 0; loop < 4; loop ++)
            {
                orangeDigits[loop] |= 0x80;
                PORTB = orangeDigits[loop];
                PORTA = 0x00;
                PORTA = 0x01;
            }
}

void HEX_SendRedNoCode(char digitRed1, char digitRed2, char digitRed3, char digitRed4)
{
            char loop = 0;
            PORTB = ENABLE_NOCODE_MultiSend;
            PORTA = 0x02;
            PORTA = 0x03;

            PORTB = digitRed1;
            PORTA = 0x00;
            PORTA = 0x01;
            
            PORTB = digitRed2;
            PORTA = 0x00;
            PORTA = 0x01;

            PORTB = digitRed3;
            PORTA = 0x00;
            PORTA = 0x01;
            
            PORTB = digitRed4;
            PORTA = 0x00;
            PORTA = 0x01;

            for(loop = 0; loop < 4; loop ++)
            {
                PORTB = 0x80;
                PORTA = 0x00;
                PORTA = 0x01;
            }

}
void HEX_DisplayRedNoCode(char digits[])
{
            char loop = 0;

            PORTB = ENABLE_NOCODE_MultiSend;
            PORTA = 0x02;
            PORTA = 0x03;

            for(loop = 0; loop < 4; loop ++)
            {
                PORTB = digits[loop];
                PORTA = 0x00;
                PORTA = 0x01;
            }
            
            for(loop = 0; loop < 4; loop ++)
            {
                PORTB = 0x80;
                PORTA = 0x00;
                PORTA = 0x01;
            }

}

void HEX_SendOrangeNoCode(char digitOragne1, char digitOrange2, char digitOrange3, char digitOrange4)
{
            char loop = 0;
            
            PORTB = ENABLE_NOCODE_MultiSend;
            PORTA = 0x02;
            PORTA = 0x03;
            
            for(loop = 0; loop < 4; loop ++)
            {
                PORTB = 0x80;
                PORTA = 0x00;
                PORTA = 0x01;
            }

            PORTB = digitOragne1;
            PORTA = 0x00;
            PORTA = 0x01;
            
            PORTB = digitOrange2;
            PORTA = 0x00;
            PORTA = 0x01;

            PORTB = digitOrange3;
            PORTA = 0x00;
            PORTA = 0x01;
            
            PORTB = digitOrange4;
            PORTA = 0x00;
            PORTA = 0x01;
}
void HEX_DisplayOrangeNoCode(char digits[])
{
            char loop = 0;

            PORTB = ENABLE_NOCODE_MultiSend;
            PORTA = 0x02;
            PORTA = 0x03;

            for(loop = 0; loop < 4; loop ++)
            {
                PORTB = 0x80;
                PORTA = 0x00;
                PORTA = 0x01;
            }
            for(loop = 0; loop < 4; loop++)
            {
                PORTB = digits[loop];
                PORTA = 0x00;
                PORTA = 0x01;
            }
}

void HEX_SendAllNoCode(char digitRed1, char digitRed2, char digitRed3, char digitRed4, char digitOragne1, char digitOrange2, char digitOrange3, char digitOrange4)
{
            PORTB = ENABLE_NOCODE_MultiSend;
            PORTA = 0x02;
            PORTA = 0x03;

            PORTB = digitRed1;
            PORTA = 0x00;
            PORTA = 0x01;
            
            PORTB = digitRed2;
            PORTA = 0x00;
            PORTA = 0x01;
            PORTB = digitRed3;
            PORTA = 0x00;
            PORTA = 0x01;
            
            PORTB = digitRed4;
            PORTA = 0x00;
            PORTA = 0x01;

            PORTB = digitOragne1;
            PORTA = 0x00;
            PORTA = 0x01;
            
            PORTB = digitOrange2;
            PORTA = 0x00;
            PORTA = 0x01;

            PORTB = digitOrange3;
            PORTA = 0x00;
            PORTA = 0x01;
            
            PORTB = digitOrange4;
            PORTA = 0x00;
            PORTA = 0x01;
}
void HEX_DisplayAllNoCode(char redDigits[], char orangeDigits[])
{
            char loop = 0;

            PORTB = ENABLE_NOCODE_MultiSend;
            PORTA = 0x02;
            PORTA = 0x03;

            for(loop = 0; loop < 4; loop++)
            {
                PORTB = redDigits[loop];
                PORTA = 0x00;
                PORTA = 0x01;
            }

            for(loop = 0; loop < 4; loop ++)
            {
                PORTB = orangeDigits[loop];
                PORTA = 0x00;
                PORTA = 0x01;
            }

}



int HEX_DigitConverter(int number)
{
            char digits[] = {0,0,0,0};
          
            while (number > 999)
              {
                  number -= 1000;
                  digits[0]++;
              }
              while (number >99)
              {
                  number -= 100;
                  digits[1]++;
              }
              while (number > 9)
              {
                  number -= 10;
                  digits[2]++;
              }
              digits[3] = number;

            return digits[0] * 16 * 16 * 16 + 
                digits[1] * 16 * 16 +
                digits[2] * 16 + digits[3];

}

char HEX_Decoder (char orignalNumber)
{
    switch (orignalNumber)
    {
    case 0:
        return NOCODE_ZERO;
    case 1: 
        return NOCODE_ONE;
    case 2:
        return NOCODE_TWO;
    case 3:
        return NOCODE_THREE;
    case 4:
        return NOCODE_FOUR;
    case 5:
        return NOCODE_FIVE;
    case 6:
        return NOCODE_SIX;
    case 7:
        return NOCODE_SEVEN;
    case 8:
        return NOCODE_EIGHT;
    case 9:
        return NOCODE_NINE;
    default:
        return NOCODE_BLANK;
    }
}

//////////////////////////////////////////////////////////////////
//      Class Mandated Functions
////////////////////////////////////////////////////////////////
// show HEX decoding (changes all of display to HEX, w/wo dp)
/* Params: (address, data, dp) */
void Segs_Normal (unsigned char address, unsigned char data, char dp)
{
    PORTB = ENABLE_HEX_SingleSend | address;
    PORTA = 0x02;
    PORTA = 0x03;

    if(dp)
    {
        PORTB = data & ~0x80;
    }
    else
    {
        PORTB = data | 0x80;
    }

    PORTA = 0x00;
    PORTA = 0x01;

}

// control segs manually
/* Params: (address, data) */
void Segs_Custom (unsigned char address, unsigned char data)
{
    PORTB = ENABLE_NOCODE_SingleSend;
    PORTB |= address;
    PORTA = 0x02;
    PORTA = 0x03;

    PORTB = data;

    PORTA = 0x00;
    PORTA = 0x01;
}

// clear the display
/* Params: (address) */
void Segs_ClearDigit(unsigned char adress)
{
    PORTB = ENABLE_NOCODE_SingleSend | adress;
    PORTA = 0x02;
    PORTA = 0x03;

    PORTB = 0x80;
    PORTA = 0x00;
    PORTA = 0x01;
};

// clear the entire display
void Segs_Clear(void)
{
    char loop = 0;

    PORTB = ENABLE_NOCODE_MultiSend;
    PORTA = 0x02;
    PORTA = 0x03;

    for(loop = 0; loop < 8; loop ++)
    {
        PORTB = 0x80;
        PORTA = 0x00;
        PORTA = 0x01;
    }
}

// clear display  upper or lower line
/* Params: (line) */
void Segs_ClearLine(Segs_LineOption line)
{
    if(line)
    {
        //Bottom
        Segs_Custom(4, NOCODE_BLANK);
        Segs_Custom(5, NOCODE_BLANK);
        Segs_Custom(6, NOCODE_BLANK);
        Segs_Custom(7, NOCODE_BLANK);

    }
    else
    {
        Segs_Custom(0, NOCODE_BLANK);
        Segs_Custom(1, NOCODE_BLANK);
        Segs_Custom(2, NOCODE_BLANK);
        Segs_Custom(3, NOCODE_BLANK);
    }
}

// show a 16-bit value on the upper or lower display
/* Params: (value, line) */
void Segs_16H (unsigned int value, Segs_LineOption line)
{
    char address = (line*4) + 3;

    Segs_Normal(address--, value,0);
    Segs_Normal(address--, value >>= 4, 0);
    Segs_Normal(address--, value >>= 4, 0);
    Segs_Normal(address--, value >>= 4, 0);
    
}

// show a decimal value on the first or second line of the 7-segs
/* Params: (value, line)*/
void Segs_16D (unsigned int value, Segs_LineOption line)
{
    char address = (line*4) + 3;

    value = HEX_DigitConverter(value);

    Segs_Normal(address--, value,0);
    Segs_Normal(address--, value >>= 4,0);
    Segs_Normal(address--, value >>= 4,0);
    Segs_Normal(address--, value >>= 4,0);
}
// show the 8-bit value starting on the digit as addr (0-6)
/* Params: (addr, value)*/
void Segs_8H (unsigned char address, unsigned char value)
{
    Segs_Normal(address--, value, 0);
    if(address >7)
    {address = 7;}
    Segs_Normal(address--, value >>= 4, 0);
}

// say Err on the appropriate line
/* Params: (line) */
void Segs_SayErr (Segs_LineOption line)
{
    if(line)
    {
        //Bottom
        Segs_Custom(4, NOCODE_E);
        Segs_Custom(5, NOCODE_LowerR);
        Segs_Custom(6, NOCODE_LowerR);
        Segs_Custom(7, NOCODE_BLANK);

    }
    else
    {
        Segs_Custom(0, NOCODE_E);
        Segs_Custom(1, NOCODE_LowerR);
        Segs_Custom(2, NOCODE_LowerR);
        Segs_Custom(3, NOCODE_BLANK);
    }
}