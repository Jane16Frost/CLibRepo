
typedef enum LCDEntryStyleTypedef_
{
    LCD_LeftType = 0x04,
    LCD_RightType = 0x06,
    LCD_LeftShift = 0x05,
    LCD_RightShift = 0x07

} LCDEntryStyle;

typedef enum LCDCursorStyleTypedef_
{
    LCD_NoCursor = 0x0C,
    LCD_Cursor = 0x0E,
    LCD_Blink = 0x0D,
    LCD_BlinkCursor = 0x0F

} LCDCursorStyle;

typedef enum LCDSizeTypedef_
{
    LCD_5x7 = 0x00,
    LCD_5x10 = 0x04

} LCDSize;

typedef enum LCDLinesTypdef_
{
    LCD_SingleLine = 0x00,
    LCD_Multiline = 0x08

}LCDLines;

typedef enum LCDShiftTypeTypeDef_
{
    LCD_ShiftDisplay =0x08,
    LCD_ShiftCursor = 0x00,
    LCD_DirectionRight = 0x04,
    LCD_DirectionLeft = 0x00

}LCDShiftType;

#define lcd_MicroDelay { char __x = 10; while (--__x); } // 20MHz Version
///////////////////////////////////////////////////////
//        Initalization Functions
///////////////////////////////////////////////////////

void LCD_Init(void);

void LCD_8BitInit(char lines, char size);
void LCD_4BitInit(char lines, char size);

void LCD_SetEntryMode(char incStyle, char cursorStyle);

void LCD_ON(char cursorStyle);
void LCD_OFF(void);

///////////////////////////////////////////////////////
//          Busy Flag Functions
//////////////////////////////////////////////////////
void WaitForBusyFlag(void);
char CheckAddress(void);
char CheckBusyFlag(void);

//////////////////////////////////////////////////////
//          Write to Display Functions
////////////////////////////////////////////////////
void LCD_WriteToDisplay(unsigned char message[], char position);
void LCD_WriteCharacterToDisplay(unsigned char character);
void LCD_WriteStringToDisplay(unsigned char *);

void LCD_ClearScreen(void);

//////////////////////////////////////////////////////
//      Create Character Functions
//////////////////////////////////////////////////////
void LCD_WriteCharacterType(char image[], char size);

//////////////////////////////////////////////////////
//         Manipulate Cursour Functions
//////////////////////////////////////////////////////
void LCD_ReturnHome(void);

void LCD_SetCGRamAddress(char address);
void LCD_SetDDRamAddress(char address);
void lcd_AddrXY (unsigned char ix, unsigned char iy);

void LCD_MoveCursor(char movementType, char direction);