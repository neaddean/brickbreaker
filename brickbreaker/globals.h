#ifndef globals_h
#define globals_h

#include "SDL.h"
#include "SDL_ttf.h"

extern SDL_Surface *screen;
extern SDL_Surface *blockerimage;
extern SDL_Surface *ballimage;
extern SDL_Surface *background;
//extern SDL_Surface *pauselayover;

extern SDL_Surface *green1;
extern SDL_Surface *orange1;
extern SDL_Surface *unbreakable;

extern TTF_Font *font;

extern const SDL_Color RED;
extern const SDL_Color BLACK;
extern const SDL_Color WHITE;

extern SDL_Event event;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SCREEN_BPP;

extern const int DOT_WIDTH;
extern const int DOT_HEIGHT;

extern const int BAR_WIDTH;
extern const int BAR_HEIGHT;

extern const int BRICK_WIDTH;
extern const int BRICK_HEIGHT;

extern const int FRAMES_PER_SECOND;

#endif