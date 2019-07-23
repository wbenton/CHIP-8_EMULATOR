/* Author: William Benton
 * Filename: chip8.h
 * Date: 2019-06-18
 */

/* Packages to include */
#include "SDL2/SDL.h"
#include <stdio.h>
#include <string.h>

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

/* Size of the opocodes in bytes */
#define OPCODE_SIZE       1

/* Mask to extract type of opcode */
#define OPCODE_MASK       0xF000

/* Opcode masks */
#define SCR_MASK          0x0000
#define SYS               0x0000
#define CLS               0x00E0
#define RET               0x00EE
#define JP                0x1000
#define CALL              0x2000
#define SE                0x3000
#define SNE               0x4000
#define SER               0x5000
#define LD                0x6000
#define ADD               0x7000
#define EIGHT_K_INSTR     0x8000
#define LDR               0x8000
#define OR                0x8001
#define AND               0x8002
#define XOR               0x8003
#define ADDC              0x8004
#define SUB               0x8005
#define SHR               0x8006
#define SUBN              0x8007
#define SHL               0x800E
#define SNER              0x9000               
#define LDI               0xA000
#define JPV0              0xB000
#define RND               0xC000
#define DRW               0xD000
#define INSTR_SKIP        0xE000
#define SKP               0xE09E
#define SKNP              0xE0A1
#define TIMER_DELAYS      0xF000
#define LDDT              0xF007
#define LDKP              0xF00A
#define LDSDT             0xF015
#define LDST              0xF018
#define ADDI              0xF01E
#define LDF               0xF029
#define LDB               0xF033
#define LDSI              0xF055
#define LDVX              0xF065

/* Constants used for default initialization */
#define PC_START_VALUE    0x200
#define FONT_SET_NUM      80

/* Constants used shift and manipulate opcodes */
#define BYTE              8
#define NIBBLE            4
#define BYTE_MAX          255
#define BIT               1
#define PIXEL_NUM         2048

/* Constants used for graphics */
#define WHITE             255
#define FULL_OPAC         255

/* CHIP 8 struct definition */
typedef struct chip8Cpu
{
  unsigned char  V[NUM_OF_REGISTERS];   /* General purpose registers (8-bit) */
  unsigned short I;                     /* Index register (16-bit)*/
  unsigned short pc;                    /* Program Counter (16-bit) */
  unsigned short stack[STACK_SIZE];     /* Stack to hold return addresses */
  unsigned short sp;                    /* Stack Pointer (16-bit) */
  unsigned short opcode;                /* Machine code instruction */
  unsigned char  delayTimer;            /* 60hz delay timer */
  unsigned char  soundTimer;            /* 60hz sound timer */
  unsigned char  memory[MEM_SIZE];      /* Memory map */
  unsigned char  key[NUM_OF_KEYS];      /* Holds key state */
  unsigned char  drawToScreenFlag;      /* Check if screen should be drawn */
  unsigned char  gfx[64 * 32];          /* Holds graphics */
  SDL_Window*    window;                /* Graphics window */
  SDL_Renderer*  renderer;              /* Graphics rederer */
  SDL_Surface*   surface;               /* Surface that is displayed on window*/
  SDL_Texture*   texture;               /* Texture */

}Chip8;

/* Function Prototypes */
void initializeChip8( Chip8 *chip8 );
void emulateCycle   ( Chip8 *chip8 );
void loadRom        ( unsigned char *memory );
void drawScreen     ( SDL_Renderer *render, unsigned char drawToScreenFlag );
void updateScreen   ( unsigned char *gfx, SDL_Renderer *renderer );

