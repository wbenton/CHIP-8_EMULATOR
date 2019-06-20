/* Author:    William Benton
 * Filename:  chip8.c
 * Date:      2019-06-19
 */

#include "chip8.h"

typedef struct chip8Cpu
{
  unsigned char  V[NUM_OF_REGISTER];   /* General purpose registers */
  unsigned short I;                    /* Index register */
  unsigned short pc;                   /* Program Counter */
  unsigned short stack[STACK_SIZE];    /* Stack to hold return addresses */
  unsigned short sp;                   /* Stack Pointer */
  unsigned short opcode;               /* Machine code instruction */
  unsigned char  memory[MEM_SIZE];     /* Memory map */
  unsigned char  key[NUM_OF_KEYS];     /* Holds key state */
}Chip8;
