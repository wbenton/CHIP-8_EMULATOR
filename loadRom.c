/* Author:    William Benton
 * Filename:  LoadRom.c
 * Date:      2019-06-20
 */

#include <errno.h>
#include <stdio.h>
#include "chip8.h"

#define ROM_PATH          "/home/william/code/CHIP-8_EMULATOR/Pong.ch8"
#define FILE_MODE         "rb"
#define FILE_OPEN_ERROR   "Error Opening File\n"
#define FILE_READ_ERROR   "Error Reading From File\n"
#define INSTR_INCR        2
#define SINGLE_INSTR      1
#define LITTLE_ENDIAN_OFF 1

void loadRom( unsigned char * memory ) {
  FILE *rom;
  unsigned char *memoryPtr = &memory[START_PROG_MEM];
  
  /* Reset errno */
  errno = 0;

  /* Open file */
  rom = fopen( ROM_PATH, FILE_MODE );

  /* Check for error when opening the file, print message if error occurs  */
  if( !rom || errno ) {
    fprintf( stderr, FILE_OPEN_ERROR );
  }

  /* TODO MAKE THIS LOOP ENDIAN INDEPENDENT */
  /* Fill memory with contents of game ROM */
  while( !feof( rom ) ) {

    /* Read entire 2 byte opcode from rom, THIS IS FOR LITTLE ENDIAN SYSTEMS */
    fread( memoryPtr + LITTLE_ENDIAN_OFF, 
      sizeof(unsigned char), SINGLE_INSTR, rom );
    fread( memoryPtr, sizeof(unsigned char), SINGLE_INSTR, rom );

    /* Increment where we are pointing in memory */
    memoryPtr += INSTR_INCR;

    /* Check if and error occurred during file reading, if so print error */
    if( ferror( rom ) ) {
      fprintf( stderr, FILE_READ_ERROR );
      return;
    }
  }
}
