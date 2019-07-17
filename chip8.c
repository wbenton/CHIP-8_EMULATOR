/* Author:    William Benton
 * Filename:  chip8.c
 * Date:      2019-06-19
 */

#include "chip8.h"

/* Create the chip8 cpu and initializing all fields to 0 */
Chip8 chip8 = {0};

int main( int argc, char **argv ) {
  
  int temp = 0;
  /* Set up memory and initialize registers to default values */
  initializeChip8( &chip8 );

  /* Load game/program into memory */
  loadRom( chip8.memory );


  while(1) {

    fprintf( stderr, "%x\n", chip8.memory[746]); 
    fprintf( stderr, "%x\n", chip8.pc );
    fprintf( stderr, "%0x\n", chip8.opcode );
    fprintf( stderr, "%u\n", chip8.sp );
    emulateCycle( &chip8 );

    updateScreen( chip8.gfx, chip8.renderer );

    if( chip8.drawToScreenFlag ) {
      drawScreen( chip8.renderer, chip8.drawToScreenFlag );
    }
    SDL_Delay(13);
  }
  
  return 0;
}

