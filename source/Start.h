/*
 *  Start.h
 *  Pac-Man Remake
 *
 *  Created by Damiano Collu on 11/07/11.
 *  Copyright 2011 Università Cagliari Informatica. All rights reserved.
 *
 */

#include <unistd.h>
#include <string.h>

#include "types.h"
#include "math.h"

/* schermata iniziale gioco, dove si preme un tasto qualunque per iniziare a giocare */
void pressStartButton (unsigned int* highscore, unsigned int* points);

/* scrive "ready" prima di iniziare a giocare */
void ready(void);

/* scrive "game over" se Pac-Man non ha più vite */
void gameover(void);

void remainingLives (Sprite* pacman, unsigned int *lifes);

void drawAllInitialPacmanLifes (Sprite* pacman, unsigned int *lifes);
