/* Author: William Benton
 * Filename: chip8.h
 * Date: 2019-06-18
 */

/* Constants used to create CHIP 8 runtime env */

/* Constants used to implements registers and runtime stack */
#define NUM_OF_REGISTERS 16
#define STACK_SIZE 16

/* Constants used to create a mapping of the screen */
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

/* Constant used for keys recognized by CHIP 8 */
#define NUM_OF_KEYS 16

/* Constants used to create Memory map */
#define MEM_SIZE 4096
#define START_INTERP_MEM 0x000
#define END_INTERP_MEM 0x1FF
#define START_PROG_MEM 0x200
#define START_ETI_MEM 0x600
#define END_PROG_MEM 0xFFF

