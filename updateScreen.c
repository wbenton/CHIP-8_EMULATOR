#include "chip8.h"

void updateScreen( unsigned char *gfx, SDL_Renderer *renderer ) {
  char* gfxItr = gfx;
  for( int row = 0; row < SCREEN_HEIGHT; ++row ) {
    for( int col = 0; col < SCREEN_WIDTH; ++col ) {
      if( *gfxItr == 1 ) {
        SDL_RenderDrawPoint( renderer, col, row ); 
      }
      ++gfxItr;
    }
  }
}
