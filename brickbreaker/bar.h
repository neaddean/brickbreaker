#ifndef bar_h
#define bar_h
#include "SDL.h"
//#include "board.h"
#include <list>

enum sides {LEFT, RIGHT, TOP, BOTTOM, NONE};

class ball
{
	int x, y;
	int xVel, yVel;
	bool attatched;

public:

	ball(int X, int Y);
	
	bool moveball(int barx, int bary);
	void showball();
	void ballbar(int barx, int bary);
	void ballbrick(sides theside);
	void handleball();
	void returncenter(int &returnx, int &returny);

};

class gameboard
{
	int level;
	int matrix[16][9];

public:
	gameboard();
	sides handlebricks(ball theball);
	void showbricks();
};


class bar
{
	int x ,y;
	int xVel, yVel;
	std::list<ball*> balls;
	bool doit;
	SDL_Surface *ballcount;
	gameboard bricks;

public:
	bar();
	void handlebar();
	void movebar();
	void showbar();
};

#endif