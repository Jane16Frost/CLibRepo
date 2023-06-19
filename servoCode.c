#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


#include "clock.h"
#include "sw_led.h"

unsigned char dutyCounter = 0;
SwState ctr = Idle;

void main(void) {
  /* put your own code here */
  


	//EnableInterrupts;
  Clock_Set6MHz();
  SWL_Init();
  _DISABLE_COP();

  PWMCLK |= 0x04;
  PWMPRCLK = 0x10;
  PWMPOL |= 0x04;
  PWMCAE &= ~0x04;
  PWMSCLB = 125;

  PWMPER2 = 240;
  PWMDTY2 = 9;

  PWME |= 0x04;

  for(;;) {
    SWL_TOG(SWL_RED);
    //_FEED_COP(); /* feeds the dog */
    if(Sw_Process(&ctr, SWL_CTR) == Pressed)
    {
      dutyCounter ++;
      if(dutyCounter > 27)
      {
        dutyCounter = 0;
      }
      PWMDTY2 = dutyCounter;
      SWL_TOG(SWL_GREEN);
    }
  
  } /* loop forever */
  /* please make sure that you never leave main */
}
