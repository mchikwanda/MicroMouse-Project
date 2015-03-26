#include "mc9s12dp256.h"
#include "derivative.h"
#include "main_asm.h"
#include "DBug12.h"
#include "ADsensors.h"
#include "init.h"
#include "maze.h"
#include "PWMmotors.h"


#define _1SEC   250     // time delay constants
#define _2SEC   500
#define _5SEC   1250
#define _10SEC  2500

#define ONvalue	0x20
#define sensorON(sensor,thresholdValue) ((thresholdValue > sensor) ? TRUE : FALSE)

void scanWalls (void)
{
   if(sensorON(readFrontSensor(), ONvalue))
      addWall(newMaze.mouseHeading);

   if(sensorON(readRightWall(), ONvalue))
      addWall((newMaze.mouseHeading + 1) % 4);

   if(sensorON(readLeftWall(), ONvalue))
      addWall((newMaze.mouseHeading + 3) % 4);
} 

void turnToBestNeighbor (void)
{
   unsigned short desiredDirection;
   signed short difference;

   desiredDirection = getBestNeighbor();
   difference = newMaze.mouseHeading - desiredDirection;

   if (difference == -3 || difference == 1)
     leftTurn();

   else if (difference == -1 || difference == 3)
     rightTurn();

   else if (difference == -2 || difference == 2)
     turn180();

   newMaze.mouseHeading = desiredDirection;
}


int main(void)
{
   init();
   
   //fwd();
   
   delay(_1SEC);
   nextCellGo();

   asm("swi");
}
