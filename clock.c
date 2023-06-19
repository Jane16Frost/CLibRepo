#include "clock.h"
#include "derivative.h"

unsigned long clockSpeed = DEF_BUS_CLOCK;

void Clock_Set6MHz(void)
{
    CLKSEL &= ~CLKSEL_PLLSEL_MASK;  //disable pll as system clock
    SYNR = 2;
    REFDV = 7;
    PLLCTL = PLLCTL_PLLON_MASK | PLLCTL_AUTO_MASK;

    while(!(CRGFLG & CRGFLG_LOCK_MASK));//Wait for PLL to lock
    
    CLKSEL |= CLKSEL_PLLSEL_MASK; 

    clockSpeed = 6000000;
}

void Clock_Set8MHZ(void) //Set clock to 8MHZ using PLL
{

    CLKSEL &= ~CLKSEL_PLLSEL_MASK;  //disable pll as system clock
    SYNR = 1;
    REFDV = 3;
    PLLCTL = PLLCTL_PLLON_MASK | PLLCTL_AUTO_MASK;

    while(!(CRGFLG & CRGFLG_LOCK_MASK));//Wait for PLL to lock
    
    CLKSEL |= CLKSEL_PLLSEL_MASK; 

    clockSpeed = 8000000;
}

void Clock_Set24MHZ(void) //Set clock to 24MHZ using PLL
{
    CLKSEL &= ~CLKSEL_PLLSEL_MASK;  //disable pll as system clock
    SYNR = 2;
    REFDV = 1;
    PLLCTL = PLLCTL_PLLON_MASK | PLLCTL_AUTO_MASK;

    while(!(CRGFLG & CRGFLG_LOCK_MASK));//Wait for PLL to lock
    
    CLKSEL |= CLKSEL_PLLSEL_MASK; 

    clockSpeed = 24000000;
}

void Clock_Set20MHZ(void) //Set clock to 20MHZ using PLL
{
    SYNR = 4;
    REFDV = 3;

    CLKSEL &= ~CLKSEL_PLLSEL_MASK;  //disable pll as system clock
    SYNR = 4;
    REFDV = 3;
    PLLCTL = PLLCTL_PLLON_MASK | PLLCTL_AUTO_MASK;

    while(!(CRGFLG & CRGFLG_LOCK_MASK));//Wait for PLL to lock
    
    CLKSEL |= CLKSEL_PLLSEL_MASK; 

    clockSpeed = 20000000;   
}

void Clock_EnableOutput(unsigned char input)  //Enable output specifying divider for it
{
    ECLKCTL = 0;
    
    ECLKCTL &= ~ECLKCTL_NECLK_MASK;

    if(input == 2)
    {
        ECLKCTL |= ECLKCTL_EDIV0_MASK;
    }
    else if(input == 3)
    {
        ECLKCTL |= ECLKCTL_EDIV1_MASK;
    }
    else if(input == 4){
        ECLKCTL |= ECLKCTL_EDIV1_MASK | ECLKCTL_EDIV0_MASK;
    }
}

unsigned long Clock_GetBusSpeed(void)	//Get Current Clock Speed
{
   return clockSpeed;
}

