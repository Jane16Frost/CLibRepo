#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */




int i = 0;
int btnCount = 0;
void main(void) {
  /* put your own code here */
  
  DDR1AD1 = 0xe0;
    ATD1DIEN1 = 0x1F;
    PT1AD1 = 0x00;
	//EnableInterrupts;


  for(;;) {
   
    btnCount = 0;
    for (i = 0; i<5; i++)
    {
    if(PT1AD1 & (1<< i) ){
      btnCount++;
    }
    }
       // PT1AD1 = 0x00; 
      PT1AD1 = btnCount << 5;
    }


  } /* loop forever */
  /* please make sure that you never leave main */

