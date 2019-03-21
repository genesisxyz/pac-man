/*
 *  Labyrinth.h
 *  Pac-Man Remake
 *
 *  Created by Damiano Collu on 25/06/11.
 *  Copyright 2011 Università Cagliari Informatica. All rights reserved.
 *
 */

#ifndef LABYRINTH
#define LABYRINTH

#include <stdlib.h>

#include "types.h"
#include "Sprite.h"
#include "Ghost.h"

/* inizializza labirinto di gioco, Pac-Man, fantasmi e pillole */
void initLabyrinth (char labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], Layer tempLabyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], Sprite* pacman, Sprite ghost[GHOSTS_NUMBER], Pills* pills);

/* reimposta pillole e ridisegna i cancelli nella "casa" dei fantasmi */
void resetPillsInLabyrinth (char labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], Layer tempLabyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], Pills *pills);

/* ridisegna tutto il labirinto e le pillole */
void resetLabyrinth (char labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], Layer tempLabyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], Pills *pills);

/* disegna un simbolo in una certa posizione */
void addCharToPosition (Point* position, chtype symbol);

/* reimposta posizioni di Pac-Man e fantasmi */
void resetSpritesPositions (Layer tempLabyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], Sprite* pacman, Sprite ghost[GHOSTS_NUMBER]);

/* fa lampeggiare il labirinto */
void labyrinthBlinking (char labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], Sprite ghost[GHOSTS_NUMBER]);

#endif
