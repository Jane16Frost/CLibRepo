#include "derivative.h"
#include "sci.h"
#include "clock.h"
#include <hidef.h> 


/* BASIC FUNCTIONS, to be coded in CMPE1250*******************************/

//SCI0 - Normal mode: RDX0-> PS0 (PIN 89), TDX0-> PS1 (PIN 90)
// set baud, returns actual baud

unsigned long sci0_Init(unsigned long ulBaudRate, int iRDRF_Interrupt)
{
    float calculatedBaudRate = Clock_GetBusSpeed() / (16*ulBaudRate);
    SCI0CR1 = 0;
    SCI0CR2 |= SCI0CR2_TE_MASK | SCI0CR2_RE_MASK;

    if(iRDRF_Interrupt)
    {
        SCI0CR2 |= SCI0CR2_RIE_MASK;
    }
    else
    {
        SCI0CR2 &= ~SCI0CR2_RIE_MASK;
    }
    
    if(calculatedBaudRate - (int)calculatedBaudRate >= 0.5)
    {
        calculatedBaudRate ++;
    }

    SCI0BD = calculatedBaudRate;
    calculatedBaudRate = Clock_GetBusSpeed() / (16* (int)calculatedBaudRate);
   
    return calculatedBaudRate;
}

// blocking byte read
// waits for a byte to arrive and returns it
unsigned char sci0_bread(void)
{
    while(!(SCI0SR1 & SCI0SR1_RDRF_MASK));
    return SCI0DRL;
}

// read a byte, non-blocking
// returns 1 if byte read, 0 if not
unsigned char sci0_rxByte(unsigned char * pData)
{

    if((SCI0SR1 & SCI0SR1_RDRF_MASK))
    {
        *pData = SCI0DRL;
        return 1;
    }
    else 
    {
        return 0;
    }
}

// receive a string from the SCI
// up to buffer size-1 (string always NULL terminated)
// number of characters is BufferSize minus one for null
// once user enters the max characters, null terminate and return
// if user enters 'enter ('\r')' before-hand, return with current entry (null terminated)
// echo valid characters (non-enter) back to the terminal
// return -1 on any error, otherwise string length
int sci0_rxStr (char * const pTarget, int BufferSize)
{
    int loop;
    for(loop = 0; loop < BufferSize; loop++)
    {
        *(pTarget + loop) = sci0_bread();
    }
}

int sci0_rxCheckFullString(char* locatioSave)
{
    char currentByte;

    do
    {
        currentByte = sci0_bread();
        *locatioSave++ = currentByte;

    } while (currentByte != '\r');
    
}

// send a byte over SCI
void sci0_txByte (unsigned char data)
{
    while(!(SCI0SR1 & SCI0SR1_TDRE_MASK));
    SCI0DRL = data;
}

// send a null-terminated string over SCI
void sci0_txStr (char const * straddr)
{
    while (*straddr != '\0')
    {
       sci0_txByte(*straddr++);
    }
    
}



/* BASIC FUNCTIONS**********************************************************/



/* Other SCIs "Available". These items are optional, for other SCI ports
SCI1 - IRDA mode for using IR module - RDX1-> PS2 (PIN 91), TDX1-> PS3 (PIN 92)
SCI2 - Shared with port J interrupts - RDX2-> PJ0 (PIN 22), TDX2-> PJ1 (PIN 21)

SCI3 - Shared with Mosfets Q7 and Q6 - RDX3-> PM6 (PIN 88), TDX3-> PM7 (PIN 87)
SCI4 - Shared with SPI2 and LCD -      RDX4-> PH4 (PIN 35), TDX4-> PH5 (PIN 34)
SCI5 - Shared with SPI2 and LCD -      RDX5-> PH6 (PIN 33), TDX5-> PH7 (PIN 32)
*/


//Advanced funtions - To Work with any sci
//int sci_Init(SCI_Base sci, unsigned long ulBaudRate, int iRDRF_Interrupt);
//unsigned char sci0_rxByte(unsigned char * pData);
//void sci_txByte (SCI_Base sci, unsigned char data);
//void sci_txStr (SCI_Base sci, char const *straddr);
//unsigned char sci_rxByte(SCI_Base sci, unsigned char * pData);
