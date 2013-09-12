//#include "board.h"
#include "sdlfuncs.h"
#include "globals.h"
#include "bar.h"
#include <iostream>
#include <fstream>
#include <cmath>



void gameboard::LoadLevel() {
	std::ifstream levelfile("levels.txt");
	level++;
	char levelfinder;
	while (1){
		levelfile >> levelfinder;
		if (levelfinder == ':') {
			levelfile >> levelfinder;
			if (levelfinder == level) break;
		}
	}
	for (int row = 0; row<16; row++){
			for (int col = 0; col<9; col++)	{
				levelfile >> matrix[row][col];
			}
		}
}

gameboard::gameboard() 
{
	level = '0';
	level_done= false;
	LoadLevel();
}

void gameboard::showbricks()
{
	bool IsLevelDone = true;
	for (int row = 0; row<16; row++)
		{
			for (int col = 0; col<9; col++)
		{
			switch (matrix[row][col])
			{
				case 0:  break;
				case 1:  apply_surface( 3+col*BRICK_WIDTH, 1+row*BRICK_HEIGHT, orange1, screen); IsLevelDone = false;    break;
				case 2:  apply_surface( 3+col*BRICK_WIDTH, 1+row*BRICK_HEIGHT, green1, screen);  IsLevelDone = false;    break;
				case 10: apply_surface( 3+col*BRICK_WIDTH, 1+row*BRICK_HEIGHT, unbreakable, screen); break;
			}
		}
	}
	if (IsLevelDone) LoadLevel();
}

double distance( int x1, int y1, int x2, int y2 )
{
    //Return the distance between the two points
    return sqrt( pow( double(x2 - x1), 2 ) + pow( double(y2 - y1), 2 ) );
}

sides gameboard::handlebricks(ball theball)
{
	int centerx, centery;
	int cX, cY;
	theball.returncenter(centerx, centery);
	sides side;

	for (int row = 0; row<16; row++)
	{
			for (int col = 0; col<9; col++)
		{
			if(matrix[row][col])
			{
				side = NONE;
				//Find closest x offset
				if( centerx < col*BRICK_WIDTH)
					{
						cX = col*BRICK_WIDTH;
						side = LEFT;
					}
				else if( centerx > col*BRICK_WIDTH + BRICK_WIDTH )
					{
						cX = col*BRICK_WIDTH + BRICK_WIDTH;
						side = RIGHT; 
					}
				else
					{
						cX = centerx;
					}
				//Find the closest y offset
				if( centery < row*BRICK_HEIGHT)
					{
						cY = row*BRICK_HEIGHT;
						side = TOP;
					}
				else if( centery > row*BRICK_HEIGHT + BRICK_HEIGHT )
					{
						cY = row*BRICK_HEIGHT + BRICK_HEIGHT;
						side = BOTTOM;
					}
				else
					{
						cY = centery;
					}

				if( distance( centerx, centery, cX, cY ) < double(DOT_WIDTH/2) )
					{
						//This box and the circle have collided
						if(matrix[row][col] != 10) matrix[row][col]--;
						return side;
					}
			}
		}
	}
	return NONE;
}