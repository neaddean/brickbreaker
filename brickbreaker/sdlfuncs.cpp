#include "SDL.h"
#include "SDL_image.h"
#include "SDL_TTF.h"
#include <string>
#include "sdlfuncs.h"
#include "globals.h"

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

	/*
	pauselayover = SDL_CreateRGBSurface(SDL_SWSURFACE, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
												0xC2000000, 0x00C20000, 0x0000C200, 0x00000032);
												//0x000000C2, 0x0000C200, 0x00C20000, 0x32000000);

	if( pauselayover == NULL )
	{
		return false;
	}
	*/

	if (TTF_Init() == -1)
	{
		return false;
	}
	
    //Set the window caption
    SDL_WM_SetCaption( "Background Test", NULL );

	srand( SDL_GetTicks() );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    // Load bar
    blockerimage = load_image( "Illustrator files\\bar3d.png" );
    if( blockerimage == NULL ) return false;

	// The ball
	ballimage = load_image("Illustrator files\\ball.png");
	if( blockerimage == NULL ) return false;

	// The font
	font = TTF_OpenFont( "consola.ttf", 28 );
	if ( font == NULL) return false;

	// The background
	background = load_image("Illustrator files\\background.png");
	if ( background == NULL ) return false;

	green1 = load_image("Illustrator files\\green2.png");
	if (green1==NULL) return false;

	orange1 = load_image("Illustrator files\\orange1.png");
	if (orange1==NULL) return false;

	unbreakable = load_image("Illustrator files\\unbreakable.png");
	if (unbreakable==NULL) return false;

    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surfaces
    SDL_FreeSurface( blockerimage );
	SDL_FreeSurface( ballimage );
	SDL_FreeSurface ( background );
	SDL_FreeSurface ( green1 );
	SDL_FreeSurface ( orange1 );
	SDL_FreeSurface ( unbreakable );

	TTF_CloseFont ( font );

	TTF_Quit();

    //Quit SDL
    SDL_Quit();
}
