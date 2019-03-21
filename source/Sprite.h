/*
 *  Sprite.h
 *  Pac-Man Remake
 *
 *  Created by Damiano Collu on 21/03/11.
 *  Copyright 2011 Università Cagliari Informatica. All rights reserved.
 *
 */

#ifndef SPRITE
#define SPRITE

#include <ncurses.h>
#include <unistd.h>

#include "types.h"
#include "Point.h"

/*
 Non modificare queste definizioni
 */
#define DEAD				0

#include "Labyrinth.h"

Sprite initSprite (unsigned int name, unsigned int bgColor, unsigned int fgColor, chtype charEyes, int startPositionX, int startPositionY);

Sprite2x1 initSprite2x1 (unsigned int name, chtype charEyes, int startPositionX, int startPositionY);

/* reimposta posizione iniziale e carattere disegnato */
void resetSprite (Sprite* sprite, chtype charEyes);

void resetMissiles (Sprite* sprite);

void drawSprite (Sprite2x1* sprite);

/* la inserisce nel labirinto come riferimento */
void drawSpriteInLabyrinth (Sprite2x1* sprite, Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS]);

void modifyColor (Sprite2x1* sprite, unsigned int colorPair);

/* modifica colore e il carattere che verrà poi disegnato */
void modifySprite (Sprite2x1* sprite, unsigned int colorPair, char charEyes);

/* somma la direzione da fare con la posizione corrente */
void setSprite2x1PositionFromLastMove (Sprite2x1* sprite);

/* somma la direzione da fare con la posizione corrente */
void setSpritePositionFromLastMove (Sprite* sprite);

/* controlla che il movimento in una data posizione sia fattibile */
bool canMove (Point* startPosition, Point* deltaPosition, Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS]);

/* cancella Sprite dal labirinto e dallo schermo  */
void eraseSprite (Point position, Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS]);

void inverseDirectionForSprite (Sprite2x1 *sprite);

#endif
