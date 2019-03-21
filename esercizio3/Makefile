CC = gcc
CFLAGS = -pedantic -Wall -c

VERSION = -D SYSTEM_V

SOURCE = ../source/

pacman: main.o Sprite.o Buffer.o Labyrinth.o math.o Init.o Pacman.o Ghost.o Missile.o Start.o LabelPlayer1.o Point.o
	$(CC) -o pacman main.o Sprite.o Buffer.o Labyrinth.o math.o Init.o Pacman.o Ghost.o Missile.o Start.o LabelPlayer1.o Point.o -lncurses -lpthread -lm
	@ echo
	@ echo Start Pac-Man Remake with ./pacman
	@ echo

main.o: $(SOURCE)main.h $(SOURCE)main.c
	$(CC) $(CFLAGS) $(VERSION) -o main.o $(SOURCE)main.c

Sprite.o: $(SOURCE)Sprite.h $(SOURCE)Sprite.c
	$(CC) $(CFLAGS) $(VERSION) -o Sprite.o $(SOURCE)Sprite.c

Buffer.o: $(SOURCE)Buffer.h $(SOURCE)Buffer.c
	$(CC) $(CFLAGS) $(VERSION) -o Buffer.o $(SOURCE)Buffer.c

Labyrinth.o: $(SOURCE)Labyrinth.h $(SOURCE)Labyrinth.c
	$(CC) $(CFLAGS) $(VERSION) -o Labyrinth.o $(SOURCE)Labyrinth.c

math.o: $(SOURCE)math.h $(SOURCE)math.c
	$(CC) $(CFLAGS) $(VERSION) -o math.o $(SOURCE)math.c

Init.o: $(SOURCE)Init.h $(SOURCE)Init.c
	$(CC) $(CFLAGS) $(VERSION) -o $(EXECUTABLE)Init.o $(SOURCE)Init.c

Pacman.o: $(SOURCE)Pacman.h $(SOURCE)Pacman.c
	$(CC) $(CFLAGS) $(VERSION) -o Pacman.o $(SOURCE)Pacman.c

Ghost.o: $(SOURCE)Ghost.h $(SOURCE)Ghost.c
	$(CC) $(CFLAGS) $(VERSION) -o Ghost.o $(SOURCE)Ghost.c

Missile.o: $(SOURCE)Missile.h $(SOURCE)Missile.c
	$(CC) $(CFLAGS) $(VERSION) -o Missile.o $(SOURCE)Missile.c

Start.o: $(SOURCE)Start.h $(SOURCE)Start.c
	$(CC) $(CFLAGS) $(VERSION) -o Start.o $(SOURCE)Start.c

LabelPlayer1.o: $(SOURCE)LabelPlayer1.h $(SOURCE)LabelPlayer1.c
	$(CC) $(CFLAGS) $(VERSION) -o LabelPlayer1.o $(SOURCE)LabelPlayer1.c

Point.o: $(SOURCE)Point.h $(SOURCE)Point.c
	$(CC) $(CFLAGS) $(VERSION) -o Point.o $(SOURCE)Point.c

clean:
	rm -f pacman *.o
