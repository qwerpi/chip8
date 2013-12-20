#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "chip8.h"

void chip8_init(int psize, char *file) {
	pixelsize = psize;

	printf("pixel size = %d\n", psize);

	printf("loading %s\n", file);

	// load file
	FILE *f = fopen(file, "rb");
	int s = fread((void *)memory, 1, 4096, f);
	fclose(f);

	// print the first 16 bytes
	for (int i = 0; i < 16; i += 2) {
		printf("%02x%02x ", memory[i], memory[i + 1]);
	}
	printf("\n");

	printf("done\n");
}

void chip8_cycle() {
	// fetch
	opcode = memory[pc] << 8 | memory[pc + 1];

	// printf("%04x\n", opcode);

	// decode and execute
	switch (opcode & 0xF000) {
		case 0x0000:
			switch (opcode & 0x00EE) {
				case 0x00E0:	// clear the screen
					for (int i = 0; i < 64 * 32; i++) {
						display[i] = 0;
					}
					drawflag = 1;
				break;

				case 0x00EE:	// return from a subroutine

				break;

				default:	// unknown
					fprintf(stderr, "Unknown opcode: %04x\n", opcode);
					exit(1);
				break;
			}
		break;

		case 0x1000:	// 1NNN - jump to address NNN

		break;

		case 0x2000:	// 2NNN - call subroutine at NNN

		break;

		case 0x3000:	// 3XNN - skip the next instruction if VX == NN

		break;

		case 0x4000:	// 4XNN - skip the next instruction if VX != NN

		break;

		case 0x5000:	// 5XY0 - skip the next instruction if VX == VY

		break;

		case 0x6000:	// 6XNN - set VX to NN

		break;

		case 0x7000:	// 7XNN - add NN to VX

		break;

		case 0x8000:	// 8XY#
			switch (opcode & 0x000F) {
				case 0x0:	// VX = VY

				break;

				case 0x1:	// VX |= VY

				break;

				case 0x2:	// VX &= VY

				break;

				case 0x3:	// VX ^= VY 

				break;

				case 0x4:	// VX += VY, VF = 1 if carry else VF = 0

				break;

				case 0x5:	// VX -= VY, VF = 0 if borrow else VF = 1

				break;

				case 0x6:	// VF = VX & 0x01, VX >>= 1

				break;

				case 0x7:	// VX = VY - VX, VF = 0 if borrow else VF = 1

				break;

				case 0xE:	// VF = VX & 0x8000, VX <<= 1

				break;

				default:	// unknown
					fprintf(stderr, "Unknown opcode: %04x\n", opcode);
					exit(1);
				break;
			}
		break;

		case 0x9000:	// 9XY0 - skip the next instruction if VX != VY

		break;

		case 0xA000:	// ANNN - set I to the address NNN

		break;

		case 0xB000:	// BNNN - jump to address NNN + V0

		break;

		case 0xC000:	// CXNN - sets VX to a random number & NN

		break;

		case 0xD000:	// DXYN - Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels.
						// Each row of 8 pixels is read as bit-coded (with the most significant bit of each byte displayed on the left) starting from memory location I
						// I value doesn't change after the execution of this instruction.
						// VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, and to 0 if that doesn't happen.

		break;

		case 0xE000:
			switch (opcode & 0x00FF) {
				case 0x9E:	// EX9E - skips the next instruction if the key stored in VX is pressed

				break;

				case 0xA1:	// EXA1 - skips the next instruction if the key stored in VX isn't pressed

				break;

				default:	// unknown
					fprintf(stderr, "Unknown opcode: %04x\n", opcode);
					exit(1);
				break;
			}
		break;

		case 0xF000:	// FX##
			switch (opcode & 0x00FF) {
				case 0x07:	// VX = delay

				break;

				case 0x0A:	// await a key press, then store in VX

				break;

				case 0x15:	// delay = VX

				break;

				case 0x18:	// sound = VX

				break;

				case 0x1E:	// I += VX

				break;

				case 0x29:	// Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.

				break;

				case 0x33:	// Stores the Binary-coded decimal representation of VX, with the most significant of three digits at the address in I,
							// the middle digit at I plus 1, and the least significant digit at I plus 2.
							// (In other words, take the decimal representation of VX, place the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.)

				break;

				case 0x55:	// stores V0 to VX in memory starting at address I

				break;

				case 0x65:	// fill V0 to VX with values from memory starting at address I

				break;

				default:	// unknown
					fprintf(stderr, "Unknown opcode: %04x\n", opcode);
					exit(1);
				break;
			}
		break;

		default:	// unknown
			fprintf(stderr, "Unknown opcode: %04x\n", opcode);
			exit(1);
		break;
	}

	// if (pc < 25)
	// 	pc += 2;

}

void chip8_draw(SDL_Surface *screen) {
	// if (drawflag) {
	// 	for (int i = 0; i < 64; i++) {
	// 		for (int j = 0; j < 32; j++) {
				
	// 		}
	// 	}
	// 	drawflag = 0;
	// }
	for(int n=0;n<1000;n++) {
		int x=rand()%800;
		int y=rand()%600;
		int pixel=rand()*100000;
		int bpp = screen->format->BytesPerPixel;
		uint8_t *p = (uint8_t *)screen->pixels + y * screen->pitch + x * bpp;

		if((x>screen->w)||(y>screen->h)||(x<0)||(y<0)) return;
			*(uint32_t *)p = pixel;

	}
}
