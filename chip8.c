/* Author:    William Benton
 * Filename:  chip8.c
 * Date:      2019-06-19
 */

#include "chip8.h"
#include <stdio.h>

/* Create the chip8 cpu and initializing all fields to 0 */
Chip8 chip8 = {0};

int main( int argc, char **argv ) {
  
  /* Set up memory and initialize registers to default values */
  initializeChip8( &chip8 );
  fprintf( stderr, "%0x\n", chip8.pc ); 

  /* Load fontset into memory */
  for( int i = 0; i < FONT_SET_NUM; ++i ) {
    fprintf( stderr, "%0x ", chip8.memory[i] );
  }

  /* Load game/program into memory */
  loadRom( &chip8.memory );

}
