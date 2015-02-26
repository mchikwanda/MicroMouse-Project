#include<stdio.h>
#include<stdbool.h>

#define NORTH	0
#define EAST 	1
#define SOUTH	2
#define WEST 	3
#define ROWS	16
#define COLUMNS	16

typedef unsigned char byte;
/*
 *	maze structure
 */
struct Maze
{
	 // vertical walls array
	 bool verticalWalls[ROWS][COLUMNS];
	 // horizontal walls array
	 bool horizontalWalls[ROWS][COLUMNS];
	 //  values array
	 byte values[ROWS][COLUMNS];

	 byte mouseRow;
	 byte mouseColumn;
	 byte mouseHeading;

	 byte targetRow;
	 byte targetColumn;
};

/* 
 *	initialize maze
 */
void initMaze (struct Maze *maze)
{
	 //initialize verticalWalls (add exterior walls)
	 for(byte i = 0;i < ROWS;i++)
	 {
		  for(byte j = 0;j<COLUMNS+1;j++)
		  {
				if(j==0 || j == COLUMNS)
				{
					 maze->verticalWalls[i][j] = true;
				}
		  }
	 }

	 //initialize horizontalWalls (add exterior walls)
	 for(byte i = 0;i < ROWS + 1;i++)
	 {
		  for(byte j=0;j<COLUMNS;j++)
		  {
				if(i==0 || i==ROWS)
				{
					 maze->horizontalWalls[i][j]=true;
				}
		  }
	 }
}

/*
 *	display maze
 */
void print(struct Maze *maze)
{
	 for(byte i = 0;i < 2*ROWS+1;i++)
	 {
		  for(byte j = 0;j < 2*COLUMNS+1;j++)
		  {
				//Add Horizontal Walls
				if(i%2 == 0 && j%2 == 1)
				{
					 if(maze->horizontalWalls[i/2][j/2] == true)
					 {
						  printf(" ---");
					 }
					 else
					 {
						  printf("    ");
					 }
				}

				//Add Vertical Walls
				if(i%2 == 1 && j%2 == 0)
				{
					 if(maze->verticalWalls[i/2][j/2] == true)
					 {
						  printf("|");
					 }
					 else
					 {
						  printf(" ");
					 }
				}

				//Add Flood Fill Values
				if(i%2 == 1 && j%2== 1)
				{
					 if((i-1)/2 == maze->mouseRow && (j-1)/2 == maze->mouseColumn)
					 {
						  if(maze->mouseHeading == NORTH)
						  {
								printf(" ^ ");
						  }
						  else if(maze->mouseHeading == EAST)
						  {
								printf(" > ");
						  }
						  else if(maze->mouseHeading == SOUTH)
						  {
								printf(" v ");
						  }
						  else if(maze->mouseHeading == WEST)
						  {
								printf(" < ");
						  }
					 }
					 else
					 {
						  byte value = maze->values[(i-1)/2][(j-1)/2];
						  if(value >= 100)
						  {
								printf("%u",value);
						  }
						  else
						  {
								printf(" ");
								printf("%u",value);
						  }
						  if(value < 10)
						  {
								printf(" ");
						  }
					 }
				}
		  }
		  printf("\n");
	 }
	 printf("\n");
}

/*
 *	create maze & display
 */
int main (void)
{
	struct Maze newMaze = {{0},{0},{0},0,0,1,7,7};
	initMaze(&newMaze);
	print(&newMaze);
	return 0;
}
