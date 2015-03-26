#ifndef hidef.h
#define hidef.h      /* common defines and macros */
#endif

#ifndef derivative.h
#define derivative.h /* derivative-specific definitions */
#endif

#ifndef main_asm.h
#define main_asm.h  /* interface to the assembly module */
#endif

#ifndef DBug12.h
#define DBug12.h
#endif

#ifndef maze.h
#define maze.h
#endif

#ifndef _1SEC
#define _1SEC   250     // time delay constants
#endif

#ifndef _5SEC
#define _5SEC   1250
#endif

#ifndef _10SEC
#define _10SEC  2500
#endif

#define STEPS   20      // # of steps to next cell
#define SpdAdjCnst  10
#define IncRightSpd (PWMDTY4+=SpdAdjCnst)    // adjust right/left wheel speed
#define DecRightSpd (PWMDTY4-=SpdAdjCnst)
#define IncLeftSpd  (PWMDTY5+=SpdAdjCnst)
#define DecLeftSpd  (PWMDTY5-=SpdAdjCnst)



/* slight left-turn */
void adjLeft (void)
{ 
   IncRightSpd;
   DecLeftSpd;  
}

/* slight right-turn */
void adjRight (void)
{ 
   IncLeftSpd;            
   DecRightSpd;  
}

/* adjust wheel speed */
void speedAdj (void) 
{
   if (PACN10==PACN32){// speed is equal, do not adjust
      ;
   }else if (PACN32> PACN10){// speed up right wheel/slow left wheel
      adjLeft();
   } else {                  // speed up left wheel/slow right wheel
      adjRight();
   }
}

void fwd (void)
{
   PTT=0;            // forward  direction
   PWMDTY4=80;
   PWMDTY5=80;
}

void stopBckp (void)
{
   PTT=0;            // forward direction
   PWMDTY4=5;
   PWMDTY5=5;
}

void stopFwd (void)
{
   PTT=0x0C;         // reverse direction
   PWMDTY4=5;
   PWMDTY5=5;
}

void bckp (void)
{
   PTT=0x0C;          // reverse direction
   PWMDTY4=100;
   PWMDTY5=100;
}


void nextCellGo (void)
{
   fwd();
   while((PACN10 < STEPS) && (PACN32 < STEPS)){
      speedAdj();
      printf("Left Wheel Count==%u   Right Wheel Count==%u\n\r",PACN32,PACN10);
   }
   stopFwd();
   PACN10=PACN32=0;  // reset wheel counters
   // update mouse coordinates
   /*newMaze.mouseRow += neighborCells[newMaze.mouseHeading][0];
   newMaze.mouseColumn += neighborCells[newMaze.mouseHeading][1];*/
   nextCell();
}

void rightTurn (void)
{
}

void leftTurn (void)
{
}

void turn180 (void)
{
}
