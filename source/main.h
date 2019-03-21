/*
 *  main.h
 *  Pac-Man Remake
 *
 *  Created by Damiano Collu on 21/03/11.
 *  Copyright 2011 Università Cagliari Informatica. All rights reserved.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <math.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h> 
#include <sys/stat.h>

#include "Buffer.h"
#include "types.h"
#include "Sprite.h"
#include "Labyrinth.h"
#include "Ghost.h"
#include "LabelPlayer1.h"
#include "Pacman.h"
#include "Start.h"
#include "Init.h"
#include "Missile.h"

/* distrugge tutti i thread (Pac-Man, fantasmi e i loro relativi missili) */
void killAllThreads (Sprite *pacman, Sprite ghost[GHOSTS_NUMBER], Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS]);
