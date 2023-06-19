#include "sw_led.h"
#include "derivative.h"

// init - must be called to init port PT1AD1
void SWL_Init (void)
{
    DDR1AD1 = 0xe0;
    ATD1DIEN1 = 0x1F;
    PT1AD1 = 0x00;
}

///////////////////////////////////////////////////////////////
// LED functions
void SWL_ON (SWL_LEDColour led)
{
    PT1AD1 |= led;
}
void SWL_OFF (SWL_LEDColour led)
{
    PT1AD1 &= ~led;
}
void SWL_TOG (SWL_LEDColour led)
{
    PT1AD1 ^= led;
}
///////////////////////////////////////////////////////////////
// special LED function
//void SWL_AUX_ON (void);
//void SWL_AUX_OFF(void);

///////////////////////////////////////////////////////////////
// switch functions

// is a specific switch being pushed (T/F)
int SWL_Pushed (SWL_SwitchPos pos)
{
    if(PT1AD1 & pos)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// is any switch being pushed (T/F)
char SWL_Any (void)
{
    if(PT1AD1 & SWL_ANY)
    {
        return 1;    
    }
    else
    {
        return 0;
    }

}

char SWL_PushedCount(void)
{
    char btnCount = 0;
    int i = 5;

    while(i)
    {
        if(PT1AD1 & (1<< i) )
        {
            btnCount++;
        }

        i--;
    }

    return btnCount;
    
}
///////////////////////////////////////////////////////////////


SwState Sw_Process(SwState* state, SWL_SwitchPos pos)
{
  
    if(PT1AD1 & pos)
    {
        if(*state == Idle)
        {
            *state = Pressed;
        }
        else
        {
            *state = Held;
        }

    }
    else
    {
        if(*state == Held)
        {
            *state = Released;
        }
        else
        {
            *state = Idle;
        }
    }

    return *state;
}