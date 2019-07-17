/* Author:    William Benton
 * Filename:  emulateCycle.c
 * Date:      2019-06-20
 */

#include "chip8.h"
#include <stdlib.h>

#define PC_INCR     2   
#define SKIP_INSTR  4
#define BYTE_MAX    255
#define BYTE        8
#define NIBBLE      4
#define E_BIT_MAX   256

void emulateCycle( Chip8 * chip8 ) {
  
  /* Extract opcode from memory */
  chip8->opcode = ((chip8->memory[chip8->pc]) << BYTE) | 
    (chip8->memory[ chip8->pc + 1]);
  fprintf( stderr, "ec-opcode: %0x\n", chip8->opcode );

  
  /* Determine the operation to be executed and then execute that operation */
  switch( chip8->opcode & OPCODE_MASK ) {
    
    case SCR_MASK:
      switch( chip8->opcode ) {
        case CLS:
          /* Clear screen */
          memset( chip8->gfx, 0, PIXEL_NUM );
          chip8->pc += PC_INCR;
          break;

        case RET:
          /* Return from function call */
          chip8->pc = chip8->stack[chip8->sp];
          chip8->sp--;
          chip8->pc += PC_INCR;
          break;
      }

    case JP:
      /* Jump to instruction */
      chip8->pc = chip8->opcode & 0x0FFF; 
      break;

    case CALL:
      /* Call subroutine */
      if( chip8->stack[chip8->sp] ) {
        chip8->sp++;
      }
      chip8->stack[chip8->sp] = chip8->pc;
      chip8->pc = chip8->opcode & 0x0FFF;
      break;

    case SE:
      /* Conditional instruction skip based on equality */
      if( chip8->V[((chip8->opcode & 0x0F00) >> BYTE)] == 
          (chip8->opcode & 0x00FF) ) {
        chip8->pc += SKIP_INSTR;
      }
      else {
        chip8->pc += PC_INCR;
      }
      break;

    case SNE:
      /* Conditional instruction skip based on equality */
      if(chip8->V[(chip8->opcode & 0x0F00) >> BYTE] != (chip8->opcode & 0x00FF)){
        chip8->pc += SKIP_INSTR;
      }
      else {
        chip8->pc += PC_INCR;
      }
      break;
    case SER:
      /* Skip instruction if Vx == Vy */
      if( chip8->V[(chip8->opcode & 0x0F00) >> BYTE] == 
           chip8->V[(chip8->opcode & 0x00F0) >> NIBBLE] ){
        chip8->pc += SKIP_INSTR;
      }
      else {
        chip8->pc += PC_INCR;
      }
      break;

    case LD:
      /* Load Vx with value */
      chip8->V[(chip8->opcode & 0x0F00) >> BYTE] = ( chip8->opcode & 0x00FF );
      chip8->pc += PC_INCR;
      break;

    case ADD:
      /* Add value in Vx with kk and put into Vx */
      chip8->V[(chip8->opcode & 0x0F00) >> BYTE] = 
        chip8->V[(chip8->opcode & 0x0F00) >> BYTE] + (chip8->opcode & 0x00FF );
      chip8->pc += PC_INCR;
      break;

    case EIGHT_K_INSTR:

      switch( (chip8->opcode) & 0xF00F ) {
        case LDR: 
          /* Put value in Vx into Vy */
          chip8->V[(chip8->opcode & 0x0F00) >> BYTE] = 
            chip8->V[(chip8->opcode & 0x00F0) >> NIBBLE];
          chip8->pc += PC_INCR;
          break;

        case OR:
          /* Vx = Vx | Vy */  
          chip8->V[(chip8->opcode & 0x0F00) >> BYTE] |= 
            chip8->V[(chip8->opcode & 0x00F0) >> NIBBLE];
          chip8->pc += PC_INCR;
          break;

        case AND:
          /* Vx = Vx & Vy */  
          chip8->V[(chip8->opcode & 0x0F00) >> BYTE] &= 
            chip8->V[(chip8->opcode & 0x00F0) >> NIBBLE];
          chip8->pc += PC_INCR;
          break;

        case XOR:
          /* Vx = Vx ^ Vy */  
          chip8->V[(chip8->opcode & 0x0F00) >> BYTE] ^= 
            chip8->V[(chip8->opcode & 0x00F0) >> NIBBLE];
          chip8->pc += PC_INCR;
          break;

        case ADDC:
          /* Vx= Vx + Vy; VF = carry */
          { 
          unsigned short addHold;
          addHold = chip8->V[(chip8->opcode & 0x0F00) >> BYTE] + 
                    chip8->V[(chip8->opcode & 0x00F0) >> NIBBLE];
          /* Set VF depending on if overflow occurred */
          if( addHold > BYTE_MAX ) {
            chip8->V[0xF] = 1;
          }
          else {
            chip8->V[0xF] = 0;
          }
          }

          /* Only keep bottom 8 bits of the addition */
          chip8->V[(chip8->opcode & 0x0F00) >> BYTE] +=
            chip8->V[(chip8->opcode & 0x00F0) >> NIBBLE];
          chip8->pc += PC_INCR;
          break;

        case SUB:
          /* Vx = Vx - Vy */  
          if( chip8->V[(chip8->opcode & 0x00F0) >> NIBBLE] >
              chip8->V[(chip8->opcode & 0x0F00) >> BYTE] ) {
            chip8->V[0xF] = 1;
          }
          else {
            chip8->V[0xF] = 0;
          }

          chip8->V[(chip8->opcode & 0x0F00) >> BYTE] -=
            chip8->V[(chip8->opcode & 0x00F0) >> NIBBLE];
          chip8->pc += PC_INCR;
          break;

        case SHR:
          /* Check what LSB and set VF accordingly */
          if( chip8->V[(chip8->opcode & 0x0F00) >> BYTE] & 0x01 ) {
            chip8->V[0xF] = 1;
          }
          else {
            chip8->V[0xF] = 0;
          }
          /* Vx = Vx SHR 1 (Vx = Vx / 2) */
          chip8->V[(chip8->opcode & 0x0F00) >> BYTE] >>= BIT;
          chip8->pc += PC_INCR;
          break; 

        case SUBN:
          /* Vx = Vy - Vx */  
          if( chip8->V[(chip8->opcode & 0x00F0) >> NIBBLE] >
              chip8->V[(chip8->opcode & 0x0F00) >> BYTE] ) {
            chip8->V[0xF] = 1;
          }
          else {
            chip8->V[0xF] = 0;
          }

          chip8->V[(chip8->opcode & 0x0F00) >> BYTE] =
            chip8->V[(chip8->opcode & 0x00F0) >> NIBBLE] - 
            chip8->V[(chip8->opcode & 0x0F00) >> BYTE];
          chip8->pc += PC_INCR;
          break;

        case SHL:
          /* Vx = Vx SHL 1 */
          /* Check what MSB and set VF accordingly */
          if( chip8->V[(chip8->opcode & 0x0F00) >> BYTE] & 0x80 ) {
            chip8->V[0xF] = 1;
          }
          else {
            chip8->V[0xF] = 0;
          }
          /* Vx = Vx SHL 1 (Vx = Vx * 2) */
          chip8->V[(chip8->opcode & 0x0F00) >> BYTE] <<= BIT;
          chip8->pc += PC_INCR;
          break; 
      }

      case SNER:
        /* If Vx != Vy skip the next instruction */
        if( chip8->V[(chip8->opcode & 0x0F00) >> BYTE] !=
            chip8->V[(chip8->opcode & 0x00F0) >> NIBBLE] ) {
          chip8->pc += SKIP_INSTR;
        }
        else {
          chip8->pc += PC_INCR;
        }
        break;

      case LDI:
        /* Set I = nnn, 0xAnnn */
        chip8->I = ( (chip8->opcode) & 0x0FFF);
        fprintf( stderr, "I: %0x\n", chip8->I );
        chip8->pc += PC_INCR;
        break;

      case JPV0:
        /* Jump to location nnn + V0, 0xBnnn */
        chip8->pc = chip8->V[0x0] + ( chip8->opcode & 0x0FFF );
        chip8->pc += PC_INCR;
        break;

      case RND:
        /* Vx gets random number */
        chip8->V[(chip8->opcode & 0x0F00) >> BYTE ] = 
          ( chip8->opcode & 0x00FF ) & ( rand() % E_BIT_MAX );
        chip8->pc += PC_INCR;
        break;

      case DRW: 
        {
        unsigned short x_row  = chip8->V[(chip8->opcode & 0x0F00) >> BYTE];
        unsigned short y_row  = chip8->V[(chip8->opcode & 0x00F0) >> NIBBLE];
        unsigned short height = chip8->opcode & 0x00F;
        unsigned short pixel;

        /* Taken from multigesture.net */
        chip8->V[0xF] = 0;
        /* Loop through the entire height of the sprite */
        for( int y = 0; y < height; ++y) {
          pixel = chip8->memory[chip8->I + y];
          /* Loop through the width of the sprite */
          for( int x = 0; x < BYTE; ++x ) {
            /* Check if pixel is on */
            if((pixel & (0x80 >> x)) != 0 ) {
              /* Check for pixel collision */
              if( chip8->gfx[(x_row + x + ((y_row + y) * 64))] ) {
                chip8->V[0xF] = 1;
              }
              chip8->gfx[x_row + x + ((y_row + y) * 64)] ^= 1;
            }
          }
        }
        chip8->drawToScreenFlag = 1;
        updateScreen( chip8->gfx, chip8->renderer );
        }
        chip8->pc += PC_INCR;
        break;
      
      case SKP:
        /* Skip next instruction if stored in Vx was pressed */
        if( chip8->key[chip8->V[(chip8->opcode & 0x0F00) >> BYTE]] ) {
          chip8->pc += SKIP_INSTR;
        }
        else {
          chip8->pc += PC_INCR;
        }
        break;

      case SKNP:
        /* Skip next instruction if stored in Vx was NOT pressed */
        if( !(chip8->key[chip8->V[(chip8->opcode & 0x0F00) >> BYTE]]) ) {
          chip8->pc += SKIP_INSTR;
        }
        else {
          chip8->pc += PC_INCR;
        }
        break;

      case TIMER_DELAYS:
        switch( chip8->opcode & 0xF0FF ) {

          case LDDT:
            /* TODO */
            /* Set Vx to the value of the delay timer */
            chip8->pc += PC_INCR;
            break;

          case LDKP:
            /* TODO */
            chip8->pc += PC_INCR;
            break;

          case LDSDT:
            /* TODO */
            chip8->pc += PC_INCR;
            break;

          case LDST:
            /* TODO */
            chip8->pc += PC_INCR;
            break;

          case ADDI:
            /* I = I + Vx */
            chip8->I += chip8->V[(chip8->opcode & 0x0F00) >> BYTE ];
            chip8->pc += PC_INCR;
            break;

          case LDF:
            {
            unsigned short sprite = chip8->opcode & 0x0F00;

            chip8->I = chip8->memory[sprite * 5];
            chip8->pc += PC_INCR;
            }
            break;

          case LDB:
            /* Load binary coded decimal representation */
            chip8->memory[chip8->I]     = 
              chip8->V[(chip8->opcode & 0x0F00) >> BYTE] / 100;

            chip8->memory[chip8->I + 1] = 
              (chip8->V[(chip8->opcode & 0x0F00) >> BYTE] / 10) % 10;

            chip8->memory[chip8->I + 2]  = 
              (chip8->V[(chip8->opcode & 0x0F00) >> BYTE] % 100) % 10;

            chip8->pc += PC_INCR;
            break;

          case LDSI:
            {
            unsigned char regNum = (chip8->opcode & 0x0F00) >> BYTE;

            /* Store regNum registers into memory */
            for( int reg = 0; reg <= regNum; ++reg ) {
              chip8->memory[chip8->I + reg] = chip8->V[reg];
            }
            chip8->pc += PC_INCR;
            }
            break;

          case LDVX:
            {
            unsigned char regNum = (chip8->opcode & 0x0F00) >> BYTE;

            /* Load registers from values in memory */
            for( int reg = 0; reg <= regNum; ++reg ) {
              chip8->V[reg] = chip8->memory[chip8->I + reg];
            }
            chip8->pc += PC_INCR;
            }
            break;

          default:
            fprintf( stderr, "Opcode: %0x\n", chip8->opcode );
            chip8->pc += PC_INCR;
            break;
        }
  }
}
