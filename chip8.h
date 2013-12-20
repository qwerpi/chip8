#ifndef __CHIP_8_H
#define __CHIP_8_H

#include <SDL/SDL.h>
#include <stdint.h>

uint8_t memory[4096];
uint16_t pc;
uint16_t opcode;

uint8_t V[16];
uint16_t I;
uint8_t stack[64];
uint16_t sp;

uint8_t delaytimer;
uint8_t soundtimer;

uint8_t display[64 * 32];
uint8_t key[16];

uint32_t pixelsize;
uint8_t drawflag;

void chip8_init(int psize, char *file);
void chip8_cycle();

void chip8_draw(SDL_Surface *screen);

#endif
