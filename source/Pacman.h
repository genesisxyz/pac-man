/*
 *  Pacman.h
 *  Pac-Man Remake
 *
 *  Created by Damiano Collu on 11/07/11.
 *  Copyright 2011 Università Cagliari Informatica. All rights reserved.
 *
 */

#ifdef THREADS

#define pacmanController_ARG void *arg

#define newPacmanController_ARG pthread_t *thread
#define newPacmanController_VALUES &pacman.name

#endif

#ifdef PROCESSES

#define pacmanController_ARG int buffer_write

#define newPacmanController_ARG pid_t* process, int buffer[2]
#define newPacmanController_VALUES &pacman.name, buffer

#endif

#ifdef SYSTEM_V

#define pacmanController_ARG void

#define newPacmanController_ARG pid_t* process
#define newPacmanController_VALUES &pacman.name

#endif

#include <string.h>

#include "types.h"
#include "Buffer.h"
#include "math.h"

/* usata dal thread Pac-Man per scrivere una nuova direzione sul buffer se viene premuto un tasto */
void* pacmanController (pacmanController_ARG);

void setNewPacmanPositionFromBuffer (Point* pacmanNextMove, struct bufferElement* element);

int scoreUpdate (unsigned int* pills, Points* points, unsigned int* highscore, Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], Point* pacmanPosition, unsigned int *hit);

/* crea un nuovo thread per Pac-Man */
void newPacmanController (newPacmanController_ARG);
