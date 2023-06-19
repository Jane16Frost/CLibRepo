#include "pit.h"
#include "derivative.h"
#include "clock.h"


void PIT_TotalInit()
{
    PITMUX = 0x80;
    PITINTE = 0xFF;
    PITCE |= 0x0F;
}

/// @brief Configures a channel (ch0 - ch3)
/// @param ch The channel in question (PIT_CH0 - PIT_CH3)
/// @param mt The micro-timer to be connected to (MT1 or MT0(default))
/// @param ie Enables or disables interrupt for the channel
void PIT_InitChannel(PIT_Channel ch, PIT_MicroTimer mt, PIT_Interrupt ie)
{
    //if Clock 1
    if(mt)
    {
        PITMUX |= ch;
    }
    //if clock 0
    else
    {
        PITMUX &= ~ch;
    }
    //Interupts enabled
    if(ie)
    {
        PITINTE |= ch;
    }
    //Interuprs diabled
    else
    {
        PITINTE &= ~ch;
    }

    PITCE |= ch;
}

/// @brief Configures the channel to a 1[ms] event, fix connection to micro-timer1 
/// @param ch The channel to be configured
void PIT_HoldForFlag(PIT_Channel ch)
{
    while (!(PITTF & ch));
    PITTF = 0x08;

}

/// @brief A blocking delay function in milliseconds
/// @param ch The channel to use with the delay
/// @param ms The number of milliseconds to delay
void PIT_Sleep(PIT_Channel ch, unsigned int ms)
{
    if(!(PITCFLMT & ch))
    {
        switch (ch)
        {
        case PIT_CH0:
            PITLD0 = Clock_GetBusSpeed() / 1000-1;
            break;
        case PIT_CH1:
            PITLD1 = Clock_GetBusSpeed() / 1000 -1;

        break;
        case PIT_CH2:
            PITLD2 = Clock_GetBusSpeed() / 1000 -1;

        break;
        case PIT_CH3:
            PITLD3 = Clock_GetBusSpeed() / 1000 -1;

            break;
        }
        PITMTLD1 = 0x00;
        PIT_InitChannel(ch, PIT_MT1, 0);
    }
        PITFLT |= ch;
        PITTF = ch;
    while (ms--)
    {
        PIT_HoldForFlag(ch);
    }
    
    
}

/// @brief This enables the PIT. It is recommened to be called last. 
///        Nothing will work if this is not called
void PIT_Start(void)
{
   // PITCFLMT |= PITCFLMT_PITFRZ_MASK;
    PITCFLMT |= PITCFLMT_PITE_MASK;
}

/// @brief Optional. Reasonable for anything above 20us
/// @param ch The channel to use with the delay
/// @param us The number of microseconds to delay
void PIT_Delay_us(PIT_Channel ch, unsigned int us)
{
    
}

//Sets channel 3 and mt 1 to Sleep Channel
void InitSleepChannel()
{
     PITMTLD1 = 0x00;
     PITLD3 = Clock_GetBusSpeed() / 1000 -1;
    PIT_InitChannel(PIT_CH3, PIT_MT1, 0);
    // PITMUX |= 0x08;

    // PITINTE &= 0x08;
    // PITCE |= 0x08;
}

//Uses channel 3 and mt 1 to sleep ms milliSeconds
void SleepMs(unsigned int ms)
{
    PITFLT |= 0x08;
    PITTF = 0x08;
    while (ms--)
    {
        PIT_HoldForFlag(PIT_CH3);
    }
    
}