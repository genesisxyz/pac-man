/*
 *  Ghost.h
 *  Pac-Man Remake
 *
 *  Created by Damiano Collu on 11/07/11.
 *  Copyright 2011 Università Cagliari Informatica. All rights reserved.
 *
 */

#ifndef GHOST_HEADER
#define GHOST_HEADER

#include <unistd.h>
#include <math.h>
#include <signal.h>

#include "types.h"
#include "Buffer.h"
#include "Sprite.h"
#include "Missile.h"

#ifdef THREADS

#define ghostNewDirection_ARG void *arg

#define newGhost_ARG pthread_t *thread, unsigned int *ghostName
#define newGhost_VALUE_ghost(n) &ghost[n].name, &ghost[n].image.name

#define ghostWaiting_ARG Sprite ghost[GHOSTS_NUMBER], Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS]
#define ghostWaiting_VALUES ghost, tempLabyrinth

#define duplicateGhosts_ARG Sprite ghost[GHOSTS_NUMBER], unsigned int ghostHits[(GHOSTS_NUMBER / 2)]
#define duplicateGhosts_VALUES ghost, ghostHits

#endif

#ifdef PROCESSES

#define ghostNewDirection_ARG unsigned int name, int buffer_write

#define newGhost_ARG pid_t* process, unsigned int* ghostName, int buffer[2]
#define newGhost_VALUE_ghost(n) &ghost[n].name, &ghost[n].image.name, buffer

#define ghostWaiting_ARG Sprite ghost[GHOSTS_NUMBER], Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], int buffer[2]
#define ghostWaiting_VALUES ghost, tempLabyrinth, buffer

#define duplicateGhosts_ARG Sprite ghost[GHOSTS_NUMBER], unsigned int ghostHits[(GHOSTS_NUMBER / 2)], int buffer[2]
#define duplicateGhosts_VALUES ghost, ghostHits, buffer

#endif

#ifdef SYSTEM_V

#define ghostNewDirection_ARG unsigned int name

#define newGhost_ARG pid_t* process, unsigned int* ghostName
#define newGhost_VALUE_ghost(n) &ghost[n].name, &ghost[n].image.name

#define ghostWaiting_ARG Sprite ghost[GHOSTS_NUMBER], Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS]
#define ghostWaiting_VALUES ghost, tempLabyrinth

#define duplicateGhosts_ARG Sprite ghost[GHOSTS_NUMBER], unsigned int ghostHits[(GHOSTS_NUMBER / 2)]
#define duplicateGhosts_VALUES ghost, ghostHits

#endif

/* usata sul thread di un fantasma, genera una nuova direzione */
void* ghostNewDirection (ghostNewDirection_ARG);

/* controlla collisioni tra Pac-Man e altri oggetti, missili e fantasmi */
unsigned int ghostHitPacman (Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], Point *position, Sprite* pacman, Sprite ghost[GHOSTS_NUMBER], unsigned int ghostHits[(GHOSTS_NUMBER / 2)]);

/* muove un fantasma */
void setNewGhostPosition (Sprite ghost[GHOSTS_NUMBER], Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], struct bufferElement* element);

/* attiva la modalità "fantasmi vulnerabili" */
void ghostsTransform (int* countdown, Sprite ghost[GHOSTS_NUMBER], unsigned int* ghostsBlinkingSchedule);

/* tiene attiva la modalità "fantasmi vulnerabili", fino alla fine */
void checkGhostsTransform (int* countdown, Sprite ghost[GHOSTS_NUMBER], unsigned int* ghostsBlinkingSchedule);

/* crea un nuovo thread per il fantasma */
void newGhost (newGhost_ARG);

/* aspetta che la posizione del fantasma non sia occupata da una pillola per creare un suo thread */
void ghostWaiting (ghostWaiting_ARG);

/* duplica i fantasmi dopo che questi vengono uccisi tutti */
void duplicateGhosts (duplicateGhosts_ARG);

/* imposta le posizioni dei primi fantasmi sotto una pillola nel labirinto */
void ghostHideUnderPill (Sprite ghost[GHOSTS_NUMBER], Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS]);

/* imposta a 0 il contatore che segna quante volte un fantasma è stato colpito */
void resetGhostHits (unsigned int ghostHits[(GHOSTS_NUMBER / 2)]);

void drawIngameGhosts (Sprite ghost[GHOSTS_NUMBER]);

#endif
