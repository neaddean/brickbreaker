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
	char level;
	int matrix[16][9];
	void LoadLevel();

public:
	bool level_done;
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
	

public:
	gameboard bricks;
	bar();
	void handlebar();
	void movebar();
	void showbar();
};

#endif