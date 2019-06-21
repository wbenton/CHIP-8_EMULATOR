/* Author: William Benton
 * Filename: chip8.h
 * Date: 2019-06-18
 */

/* Constants used to create CHIP 8 runtime env */

/* Constants used to implements registers and runtime stack */
#define NUM_OF_REGISTERS 16
#define STACK_SIZE       16

/* Constants used to create a mapping of the screen */
#define SCREEN_WIDTH  64
#define SCREEN_HEIGHT 32

/* Constant used for keys recognized by CHIP 8 */
#define NUM_OF_KEYS 16

/* Constants used to create Memory map */
#define MEM_SIZE          4096
#define START_INTERP_MEM  0x000
#define END_INTERP_MEM    0x1FF
#define START_FONT_SET    0x050
#define END_FONT_SET      0x0A0
#define START_PROG_MEM    0x200
#define START_ETI_MEM     0x600
#define END_PROG_MEM      0xFFF

/* Constants used for default initialization */
#define PC_START_VALUE    0x200
#define FONT_SET_NUM      80

/* CHIP 8 struct definition */
typedef struct chip8Cpu
{
  unsigned char  V[NUM_OF_REGISTER];   /* General purpose registers (8-bit) */
  unsigned short I;                    /* Index register (16-bit)*/
  unsigned short pc;                   /* Program Counter (16-bit) */
  unsigned short stack[STACK_SIZE];    /* Stack to hold return addresses */
  unsigned short sp;                   /* Stack Pointer (16-bit) */
  unsigned short opcode;               /* Machine code instruction */
  unsigned char  memory[MEM_SIZE];     /* Memory map */
  unsigned char  key[NUM_OF_KEYS];     /* Holds key state */
  unsigned char  drawToScreenFlag;     /* Check if screen should be drawn */
}Chip8;


/* Chip 8 Instruction masks */

/* Function Prototypes */
void initializeChip8( Chip8 * chip8 );
void emulateCycle   ( Chip8 * chip8 );
void loadRom        ( unsigned char * memory[MEM_SIZE] );
