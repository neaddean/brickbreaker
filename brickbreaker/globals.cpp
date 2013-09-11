#include "globals.h"
#include "SDL.h"
#include "SDL_ttf.h"

SDL_Surface *screen       = NULL;
SDL_Surface *blockerimage = NULL;
SDL_Surface *ballimage    = NULL;
SDL_Surface *background   = NULL;
//SDL_Surface *pauselayover = NULL;

SDL_Surface *green1		  = NULL;
SDL_Surface *orange1	  = NULL;
SDL_Surface *unbreakable  = NULL;

TTF_Font *font = NULL;

const SDL_Color RED   = {225, 0  , 0  };
const SDL_Color BLACK = {0  , 0  , 0  };
const SDL_Color WHITE = {255, 255, 255};

SDL_Event event;

const int SCREEN_WIDTH  = 1005;
const int SCREEN_HEIGHT = 742;
const int SCREEN_BPP    = 32;

const int DOT_WIDTH  = 19;
const int DOT_HEIGHT = 19;

const int BAR_WIDTH  = 297;
const int BAR_HEIGHT = 50;

const int BRICK_WIDTH = 111;
const int BRICK_HEIGHT = 40;

const int FRAMES_PER_SECOND = 70;
