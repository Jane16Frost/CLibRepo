// 8 digit Hex  library
// Revision History:

// enum to describe LED indicator positions
// tag values represent actual bit positions

typedef enum Enable_Display_CodesTypedef_
{
    ENABLE_HEX_MultiSend = 0xD0,
    ENABLE_HEX_SingleSend = 0x50,
    ENABLE_BCODE_MultiSend = 0xE0,
    ENABLE_BCODE_SingleSend = 0x60,
    ENABLE_NOCODE_MultiSend = 0xF0,
    ENABLE_NOCODE_SingleSend = 0x70,
    DISABLE_DISPLAY = 0x00,
    TOG_SEND = 0x80

}Enable_Display_Code;

typedef enum HEXNumbersTypedef_
{
    HEX_ZERO = 0x80,
    HEX_ONE = 0x81,
    HEX_TWO = 0x82,
    HEX_THREE = 0x83,
    HEX_FOUR = 0x84,
    HEX_FIVE = 0x85,
    HEX_SIX = 0x86,
    HEX_SEVEN = 0x87,
    HEX_EIGHT = 0x88,
    HEX_NINE = 0x89, 
    HEX_A = 0x8A,
    HEX_B = 0x8B,
    HEX_C = 0x8C,
    HEX_D = 0x8D,
    HEX_E = 0x8E,
    HEX_F = 0x8F,
    HEX_ZERO_DOT = 0x00,
    HEX_ONE_DOT = 0x01,
    HEX_TWO_DOT =0x02,
    HEX_THREE_DOT = 0x03,
    HEX_FOUR_DOT = 0x04,
    HEX_FIVE_DOT = 0x05,
    HEX_SIX_DOT = 0x06,
    HEX_SEVEN_DOT = 0x07,
    HEX_EIGHT_DOT = 0x08,
    HEX_NINE_DOT = 0x09, 
    HEX_A_DOT = 0x0A,
    HEX_B_DOT = 0x0B,
    HEX_C_DOT = 0x0C,
    HEX_D_DOT = 0x0D,
    HEX_E_DOT = 0x0E,
    HEX_F_DOT = 0x0F

} HEX_numbers;

typedef enum BCodeNumberdTypedef_
{
    BCODE_ZERO = 0x80,
    BCODE_ONE = 0x81,
    BCODE_TWO = 0x82,
    BCODE_THREE = 0x83,
    BCODE_FOUR = 0x84,
    BCODE_FIVE = 0x85,
    BCODE_SIX = 0x86,
    BCODE_SEVEN = 0x87,
    BCODE_EIGHT = 0x88,
    BCODE_NINE = 0x89,
    BCODE_DASH = 0x8A,
    BCODE_E = 0x8B,
    BCODE_H = 0x8C,
    BCODE_L = 0x8D,
    BCODE_P = 0x8E,
    BCODE_BLANK = 0x8F,
    BCODE_ZERO_DOT = 0x00,
    BCODE_ONE_DOT = 0x01,
    BCODE_TWO_DOT = 0x02,
    BCODE_THREE_DOT = 0x03,
    BCODE_FOUR_DOT = 0x04,
    BCODE_FIVE_DOT = 0x05,
    BCODE_SIX_DOT = 0x06,
    BCODE_SEVEN_DOT = 0x07,
    BCODE_EIGHT_DOT = 0x08, 
    BCODE_NINE_DOT = 0x09, 
    BCODE_DASH_DOT = 0x0A,
    BCODE_E_DOT = 0x0B,
    BCODE_H_DOT = 0x0C,
    BCODE_L_DOT = 0x0D,
    BCODE_P_DOT = 0x0E,
    BCODE_BLANK_DOT = 0x0F

}BCODE_numbers;

typedef enum NoCodeNumberedTypedef_
{
    NOCODE_ZERO = 0xFB,
    NOCODE_ONE = 0xB0,
    NOCODE_TWO = 0xED,
    NOCODE_THREE = 0xF5,
    NOCODE_FOUR = 0xB6,
    NOCODE_FIVE = 0xD7,
    NOCODE_SIX = 0xDF,
    NOCODE_SEVEN = 0xF0,
    NOCODE_EIGHT = 0xFF,
    NOCODE_NINE = 0xF7,
    NOCODE_BLANK = 0x80,
    NOCODE_DASH = 0x84,
    NOCODE_UNDERSCORE = 0x81,
    NOCODE_TOPLINE = 0xC0,
    NOCODE_HorizontalBorder,
    NOCODE_VerticalBorder,
    NOCODE_A = 0xFE, 
    NOCODE_LowerB = 0x9F,
    NOCODE_C = 0xCB,
    NOCODE_RevC,
    NOCODE_LowerC = 0x8D, 
    NOCODE_LowerD = 0xBD, 
    NOCODE_E = 0xCF,
    NOCODE_F = 0xCE, 
    NOCODE_SadG,
    NOCODE_H = 0xBE,
    NOCODE_LowerH = 0x9E,
    NOCODE_J = 0xB9, 
    NOCODE_L = 0x8B, 
    NOCODE_LowerL = 0x8A, 
    NOCODE_LowerN,
    NOCODE_LowerO = 0x9D,
    NOCODE_P = 0xEE,
    NOCODE_LowerR = 0x8C,
    NOCODE_U = 0xBB,
    NOCODE_LowerU = 0x99,
    NOCODE_CAP = 0xE2,
    NOCODE_BackwardSeven = 0xCA,
    NOCODE_BackwardL = 0xB1

}NOCODE_numbers;

typedef enum Segs_LineOption_
{
  Segs_LineTop = 0, 
  Segs_LineBottom = 1
} Segs_LineOption;

// init - must be called to init port PT1AD1
void HEX_Init(void);
void HEX_Off(void);

///////////////////////////////////////////////////////////////
//      Display Variables, Hex functions
///////////////////////////////////////////////////////////////

void HEX_SendAllHexCode(char digitRed1, char digitRed2, char digitRed3, char digitRed4, char digitOragne1, char digitOrange2, char digitOrange3, char digitOrange4);
void HEX_DisplayAllHexCode(char redDigits[], char orangeDigits[]);

void HEX_SendRedBCode(char digitRed1, char digitRed2, char digitRed3, char digitRed4);
void HEX_DisplayRedBCode(char digits[]);

void HEX_SendOrangeBCode(char digitOragne1, char digitOrange2, char digitOrange3, char digitOrange4);
void HEX_DisplayOrangeBCode(char digits[]);

void HEX_SendAllBCode(char digitRed1, char digitRed2, char digitRed3, char digitRed4, char digitOragne1, char digitOrange2, char digitOrange3, char digitOrange4);
void HEX_DisplayAllBCode(char redDigits[], char orangeDigits[]);

void HEX_SendRedNoCode(char digitRed1, char digitRed2, char digitRed3, char digitRed4);
void HEX_DisplayRedNoCode(char digits[]);

void HEX_SendOrangeNoCode(char digitOragne1, char digitOrange2, char digitOrange3, char digitOrange4);
void HEX_DisplayOrangeNoCode(char digits[]);

void HEX_SendAllNoCode(char digitRed1, char digitRed2, char digitRed3, char digitRed4, char digitOragne1, char digitOrange2, char digitOrange3, char digitOrange4);
void HEX_DisplayAllNoCode(char redDigits[], char orangeDigits[]);

//////////////////////////////////////////////////////////////////
//      Hex Function Variable Maniplators
//////////////////////////////////////////////////////////////////
int HEX_DigitConverter(int number);

char HEX_Decoder (char orignalNumber);

//////////////////////////////////////////////////////////////////
//      Class Mandated Functions
////////////////////////////////////////////////////////////////
// show HEX decoding (changes all of display to HEX, w/wo dp)
/* Params: (address, data, dp) */
void Segs_Normal (unsigned char, unsigned char, char);

// control segs manually
/* Params: (address, data) */
void Segs_Custom (unsigned char, unsigned char);

// clear the display
/* Params: (address) */
void Segs_ClearDigit(unsigned char);

// clear the entire display
void Segs_Clear(void);

// clear display  upper or lower line
/* Params: (line) */
void Segs_ClearLine(Segs_LineOption);

// show a 16-bit value on the upper or lower display
/* Params: (value, line) */
void Segs_16H (unsigned int, Segs_LineOption);

// show a decimal value on the first or second line of the 7-segs
/* Params: (value, line) */
void Segs_16D (unsigned int, Segs_LineOption);

// show the 8-bit value starting on the digit as addr (0-6)
/* Params: (addr, value) */
void Segs_8H (unsigned char, unsigned char);

// say Err on the appropriate line
/* Params: (line) */
void Segs_SayErr (Segs_LineOption);

