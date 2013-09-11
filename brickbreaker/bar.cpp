#include "SDL_ttf.h"
#include "bar.h"
#include "sdlfuncs.h"
#include "globals.h"
#include <list>
#include <sstream>

bar::bar()
{
	 x = (SCREEN_WIDTH-BAR_WIDTH)/2;
	 y = SCREEN_HEIGHT-BAR_HEIGHT;
	 xVel = yVel = 0;
	 for (int i = 0; i < 1; i++)	 balls.push_back(new ball(x+(BAR_WIDTH-DOT_WIDTH)/2,y-DOT_HEIGHT));	
	 doit = false;   
	 ballcount = NULL;
}

void bar::handlebar()
{
    if( event.type == SDL_KEYDOWN )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_LEFT:  xVel -= 6; break;
            case SDLK_RIGHT: xVel += 6; break;
			case SDLK_a:     doit = true; break; 
		//	balls.push_back(new ball(x+(BAR_WIDTH-DOT_WIDTH)/2,y-DOT_HEIGHT)); break;
        }
    }
    else if( event.type == SDL_KEYUP )
    {
		switch( event.key.keysym.sym )
        {
            case SDLK_LEFT:  xVel += 6; break;
            case SDLK_RIGHT: xVel -= 6; break;
			case SDLK_a:   doit = false;
        }
    }

	for (std::list<ball*>::iterator balltodo = balls.begin(); balltodo != balls.end(); ++balltodo)
	{
		(*balltodo)->handleball();
	};
}

void bar::movebar()
{
	x += xVel;

	if (x < 0 || x + BAR_WIDTH > SCREEN_WIDTH)
	{
		x -= xVel;
	}
	for (std::list<ball*>::iterator balltodo = balls.begin(); balltodo != balls.end(); )
	{
		if( (*balltodo)->moveball(x,y) )
		{
			delete * balltodo;
			balltodo = balls.erase(balltodo);
		}
		else 
		{
			(*balltodo)->ballbar(x,y);
			(*balltodo)->ballbrick(bricks.handlebricks(**balltodo));
			balltodo++;
		}
	} 

	if (doit) balls.push_back( new ball(x+(BAR_WIDTH-DOT_WIDTH)/2,y-DOT_HEIGHT));
	
	std::stringstream out; 
	out << balls.size();
	SDL_FreeSurface( ballcount );
	ballcount = TTF_RenderText_Solid(font, out.str().c_str(), WHITE );
}

void bar::showbar()
{
	bricks.showbricks();

	apply_surface(x, y, blockerimage, screen);
	apply_surface(SCREEN_WIDTH-ballcount->w, 0, ballcount, screen);

	for (std::list<ball*>::iterator balltodo = balls.begin(); balltodo != balls.end(); ++balltodo)
	{
		(*balltodo)->showball();
	}
}

ball::ball(int X, int Y)
{
	x = X;
	y = Y;

	attatched = false;

	xVel =  -4 + rand() % 8;
	yVel =  -2 - rand() % 4;
}

bool ball::moveball(int barx, int bary)
{
	if (!attatched)
	{
		x += xVel;
		y += yVel;

		if (x <= 0 || x + DOT_WIDTH  >= SCREEN_WIDTH)  
			xVel = -xVel;

		if (y <= 0) 
			yVel = -yVel;
		
		if (y >= SCREEN_HEIGHT)
			//yVel = -yVel;
			return true;
	}
	else
	{
		x = barx+(BAR_WIDTH-DOT_WIDTH)/2;
		y = bary-DOT_HEIGHT;
	}

	return false;
}

void ball::showball()
{
	apply_surface(x, y, ballimage, screen);
}

void ball::handleball()
{
	if( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
    {
       attatched = false;
    }
}

void ball::ballbar(int barx, int bary)
{
	//right side
	if (y > bary && x < barx + BAR_WIDTH && x + DOT_WIDTH > barx + BAR_WIDTH)
	{
		xVel = -xVel;
		x = barx + BAR_WIDTH;
	}
	//left side
	else if (y > bary && x < barx             && x + DOT_WIDTH > barx            )
	{
		xVel = -xVel;
		x = barx - DOT_WIDTH;
	}
	//check the top of the bar
	else if (y + DOT_HEIGHT > bary      && x > barx             && x < barx + BAR_WIDTH)
	{
		float offset = float (x - barx - BAR_WIDTH/2);
		// right side
		if(offset > 0)
		{
			xVel = int (1+6*offset/(BAR_WIDTH/2));
			if (xVel < 0) xVel = -xVel;

			yVel = int (-6+offset*2/BAR_WIDTH*4);
			y = bary - DOT_HEIGHT;
		}
		// left side
		else if (offset < 0)
		{
			offset = -offset;
			xVel = int (1+6*offset/(BAR_WIDTH/2));
			if (xVel > 0) xVel = -xVel;

			yVel = int (-6+offset*2/BAR_WIDTH*4);
			y = bary - DOT_HEIGHT;

/*				offset = -offset;
			xVel = int (2+8*offset/(BAR_WIDTH/2));
			if (xVel > 0) xVel = -xVel;

			yVel = int (-9+offset*2/BAR_WIDTH*5);
			y = bary - DOT_HEIGHT;
*/
		}
		// center
		else 
		{
			yVel = -yVel;
			if (xVel == 0) xVel = -1 + (rand() % 3);
			y = bary - DOT_HEIGHT;
		}
	}
}

void ball::returncenter(int &returnx, int &returny)
{
	returnx = int(x + DOT_WIDTH/2);
	returny = int(y + DOT_HEIGHT/2);
}

void ball::ballbrick(sides theside)
{
	switch (theside)
	{
	case LEFT:
		x -= xVel - 1;
		y -= yVel;
		xVel = -xVel;
		break;

	case RIGHT:
		x -= xVel + 1;
		y -= yVel;
		xVel = -xVel;
		break;

	case TOP:
		x -= xVel;
		y -= yVel + 1;
		yVel = -yVel;
		break;

	case BOTTOM:
		x -= xVel;
		y -= yVel - 1;
		yVel = -yVel;
		break;

	}

	return;
};
