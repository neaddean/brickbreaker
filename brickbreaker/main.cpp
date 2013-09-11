#include "SDL.h"
#include "SDL_image.h"

#include "timer.h"
#include "sdlfuncs.h"
#include "bar.h"
#include "board.h"
#include "globals.h"

#include <string>
#include <sstream>

int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;
	bool paused = false;
	bool first = false;

    //The frame rate regulator
    Timer fps;
	
	int frame = 0;

	Timer fpscalc;

    //Initialize
    if( init() == false ) return 1;

    //Load the files
    if( load_files() == false ) return 2;

	bar blocker;

	fpscalc.start();
    //While the user hasn't quit
    while( quit == false )
    {
        //Start the frame timer
        fps.start();

        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
			blocker.handlebar();
            //If the user has Xed out the window
			if( event.type == SDL_QUIT)
            {
                quit = true;
            }
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q)
			{
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
			{
				paused ^= true;
			}
        }

		if(!paused) 
		{
			blocker.movebar();
		}
		SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 192, 192, 192 ) );

		/*
		for (int i = 0; i<9; i++)
		{
			for (int j = 0; j<8; j++)
			{
				apply_surface( 3+i*BRICK_WIDTH, 1+j*BRICK_HEIGHT, green1, screen);
			}
		} */

		blocker.showbar();

        //Update the screen
		if(SDL_Flip(screen) == -1) return 1;

		frame++;

        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }

		if( fpscalc.get_ticks() > 1000 )
        {
            //The frame rate as a string
            std::stringstream caption;
            
            //Calculate the frames per second and create the string
            caption << "Average Frames Per Second: " << frame / ( fpscalc.get_ticks() / 1000.f );
            
            //Reset the caption
            SDL_WM_SetCaption( caption.str().c_str(), NULL );
            
			fpscalc.start();
			frame = 0;
        }

		if (first)
		{
			first = false;
			paused = true;
		}
    }

    //Clean up
    clean_up();

    return 0;
}
