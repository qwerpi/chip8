FLAGS = -O3 -std=c99 -lSDL
CFILES = $(wildcard *.c)

all: emu

emu: $(CFILES)
	gcc -o emu $(CFILES) $(FLAGS)

test: emu
	./emu 20 hello.c8

clean:
	rm -f emu
