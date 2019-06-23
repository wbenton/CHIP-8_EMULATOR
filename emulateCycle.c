/* Author:    William Benton
 * Filename:  emulateCycle.c
 * Date:      2019-06-20
 */

#include "chip8.h"

void emulateCycle( Chip8 * chip8 ) {
  
  /* Extract opcode from memory */
  chip8->opcode = ((chip8->memory[chip8->pc]) << SHIFT_BYTE_UP) | 
    (chip8->memory[ chip8->pc + 1]);

  /*
  switch( opcode & OPCODE_MASK ) {
    
    case 
  } */
}
