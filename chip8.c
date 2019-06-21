/* Author:    William Benton
 * Filename:  chip8.c
 * Date:      2019-06-19
 */

#include "chip8.h"

/* Create the chip8 cpu and initializing all fields to 0 */
Chip8 chip8;

int main( int argc, char **argv ) {
  
  /* Set up memory and initialize registers to default values */
  initializeChip8( &chip8 );

  /* Load game/program into memory */
  loadRom( &chip8.memory );

}
