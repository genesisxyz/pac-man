/*
 *  Missile.h
 *  Pac-Man Remake
 *
 *  Created by Damiano Collu on 11/07/11.
 *  Copyright 2011 Università Cagliari Informatica. All rights reserved.
 *
 */

#ifndef MISSILE_HEADER
#define MISSILE_HEADER

#include <sys/types.h>
#include <unistd.h>

#include "Buffer.h"
#include "Sprite.h"
#include "Ghost.h"

#ifdef THREADS

#define newMissile_ARG pthread_t *thread, unsigned int* missileName

#define missileShot_ARG void* arg

#define prepareMissile_ARG Sprite* sprite, Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS]

#endif

#ifdef PROCESSES

#define newMissile_ARG pid_t* process, unsigned int* missileName, int buffer[2]

#define missileShot_ARG unsigned int name, int buffer_write

#define prepareMissile_ARG Sprite* sprite, Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], int buffer[2]

#endif

#ifdef SYSTEM_V

#define newMissile_ARG pthread_t *thread, unsigned int* missileName

#define missileShot_ARG void* arg

#define prepareMissile_ARG Sprite* sprite, Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS]

#endif

void newMissile (newMissile_ARG);

/* usato dal thread missile per "generare" una nuova posizione */
void* missileShot (missileShot_ARG);

/* controlla che i missili si possano lanciare e li crea */
void prepareMissile (prepareMissile_ARG);

unsigned int missileMove (unsigned int* missileName, Sprite *pacman, Sprite ghost[GHOSTS_NUMBER], unsigned int ghostHits[(GHOSTS_NUMBER / 2)], Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS]);

void killMissile (Missile *missile, Sprite *sprite, Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS]);

#endif
