#ifndef hidef.h
#define hidef.h      /* common defines and macros */
#endif

#ifndef derivative.h
#define derivative.h /* derivative-specific definitions */
#endif




/* initialize registers */
void init (void){

/* Initialize A/D registers & start conversions */
  ATD1DIEN=0;            // enable analog input
  ATD1CTL2=0x80;         // ADPU=1 Enable A/D, & wait for warm up 
  wait20us();
  ATD1CTL3=0x28;         // 5 conversions per sequence
  ATD1CTL4=0xE5;         // 8 bit conversions, 7 us/conversion
  ATD1CTL5=0xB0;         // right justified, unsigned, continuos conversions, multi @ 0 

/* Initialize Port T */
  DDRT=0x0;             // x0C, PT2 & PT3 output, input @ PT0 & PT1, PT4-PT7
  //RDRT=0;                // disable reduced drive
  PACTL=0x50;            // enable 16-bit counters, no interupts, rising edge
  TCTL4=1;
  PBCTL=0x40;
  
 /* Initialize PWM registers */
  PWMCLK=0x30;      // use clock SA on channel 4 & 5      
  PWMPRCLK=0x02;    // clock A prescale = 4
  PWMSCLA=150;      // clock SB prescale = 50
  PWMPOL=0xF0;      // output high on period start
  PWMCAE=0;         // left-alingned
  PWMCTL=0x0C;      // 8-bit mode, stop PWM in wait & freeze mode
  
  PWMPER4=200;      // set period
  PWMPER5=200;  
  PWMDTY4=0;        // set 0% duty cycle, (4=>right wheel/5=>left wheel)
  PWMDTY5=0; 
  PWMCNT4=0;        // reset counters
  PWMCNT5=0;
  PWME=0x30;        // enable channel 4 & 5
 
  PACN10=0;         // reset wheel counters, (PACN10==right/PACN32==left)
  PACN32=0;  
}