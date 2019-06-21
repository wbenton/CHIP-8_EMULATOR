/* Author:    William Benton
 * Filename:  emulateCycle.c
 * Date:      2019-06-20
 */

void emulateCycle( Chip8 * chip8 ) {
  
  /* Extract opcode from memory */
  opcode = chip8->memory << SHIFT_BYTE_UP | memory[ pc + 1];  

  /*
  switch( opcode & OPCODE_MASK ) {
    
    case 
  } */
}
