//Clock System Library
//Processor: MC9S12XDP512
//Crystal: 16 MHz
//by Carlos Estay
//January 2022
//Ddit, October 6th, 2022
//Simplified, February 6th, 2023
//Removed asembly function and clock factor

#define EnableInterrupts   {__asm CLI;}
#define asm _asm

#define DEF_BUS_CLOCK 8000000

void Clock_Set6MHz(void);
void Clock_Set8MHZ(void); //Set clock to 8MHZ using PLL
void Clock_Set24MHZ(void); //Set clock to 24MHZ using PLL
void Clock_Set20MHZ(void); //Set clock to 20MHZ using PLL
void Clock_EnableOutput(unsigned char);  //Enable output specifying divider for it
unsigned long Clock_GetBusSpeed(void);	//Get Current Clock Speed
unsigned int Clock_GetFactor(void);	//Get Factor on 8 bus clock


//These Functions we will implement later
void RTI_Init(void(*function)(void));
void RTI_Delay_ms(int timeout);
