#include "chip8.h"

void drawScreen( SDL_Renderer *renderer, unsigned char drawToScreenFlag  ) {

  SDL_RenderPresent( renderer );
  drawToScreenFlag = 0;
}
