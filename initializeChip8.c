/* Author:    William Benton
 * Filename:  initializeChip8.c
 * Date:      2019-06-20
 */

#include "chip8.h"

static unsigned char chip8_fontset[FONT_SET_NUM] =
{ 
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void initializeChip8( Chip8 * chip8 ) {
  /* Position pc to start of program instructions */
  chip8->pc = PC_START_VALUE;

  /* Load fontset into memory */
  /* Changed where the font set is saved to memeory */
  unsigned char fontIter = 0;
  for( int i = START_FONT_SET; i < END_FONT_SET; ++i ) {
    chip8->memory[i] = chip8_fontset[fontIter];
    fontIter++;
  }

  SDL_Init( SDL_INIT_VIDEO );

  /* Create window to that will display the screen */
  chip8->window    = SDL_CreateWindow("Chip8 Emulator", SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

  /* Create the renderer which will allow for gpu accelerated graphics */
  chip8->renderer  = SDL_CreateRenderer(chip8->window, -1, 
    SDL_RENDERER_ACCELERATED); 

  /* Create the window with the renderer */
  SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &(chip8->window),
    &(chip8->renderer));

  /* Set the render color to WHITE */
  SDL_SetRenderDrawColor(chip8->renderer, WHITE, WHITE, WHITE, FULL_OPAC );
}
