#ifndef sdlfuncs_h
#define sdl_funcs_h

#include <string>
#include "SDL.h"

SDL_Surface *load_image( std::string filename );

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );

bool init();

bool load_files();

void clean_up();

#endif