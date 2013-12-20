#include <stdint.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <sys/time.h>
#include "chip8.h"

unsigned long timediff(struct timeval t1, struct timeval t2) {
	return (t2.tv_sec-t1.tv_sec)*1000000LL + t2.tv_usec-t1.tv_usec;
}

int main(int argc, char **argv) {

	if (argc < 3) {
		printf("Usage: ./emu <pixel_size> <filename>\n");
		return 1;
	}

	// initialize graphics
	SDL_Surface *screen;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Failed SDL_Init\n");
		return 1;
	}
	screen = SDL_SetVideoMode(800, 600, 32, SDL_ANYFORMAT);
	if (screen == NULL) {
		fprintf(stderr, "Failed SDL_SetVideoMode: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	// initialize chip8
	chip8_init(atoi(argv[1]), argv[2]);

	int cont = 1;

	struct timeval t1, t2;

	// main loop
	while (cont) {
		SDL_Flip(screen);
		SDL_LockSurface(screen);

		// emulate
		gettimeofday(&t1, NULL);
		chip8_cycle();

		// draw
		chip8_draw(screen);
		gettimeofday(&t2, NULL);

		printf("%ld\n", timediff(t1, t2));

		// get key events
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				cont = 0;
				break;
			}
			if (event.key.keysym.sym == SDLK_c) {
				SDL_FillRect(screen,NULL,0);
			}
			if (event.key.keysym.sym == SDLK_q) {
				cont = 0;
				break;
			}
		}

		// SDL_Delay(10);

		SDL_UnlockSurface(screen);
	}
	SDL_Quit();

	return 0;
}
