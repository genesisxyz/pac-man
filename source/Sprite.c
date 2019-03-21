/*
 *  Sprite.c
 *  Pac-Man Remake
 *
 *  Created by Damiano Collu on 21/03/11.
 *  Copyright 2011 Università Cagliari Informatica. All rights reserved.
 *
 */

#include "Sprite.h"

Sprite initSprite (unsigned int name, unsigned int bgColor, unsigned int fgColor, chtype charEyes, int startPositionX, int startPositionY) {

	Sprite sprite;
	
	int i;
	
	/* sostituire con funzione initSprite2x1 */
	sprite.image.name = name;
	sprite.image.colorPair = name;
	sprite.image.charEyes = charEyes;
	sprite.image.position.x = startPositionX;
	sprite.image.position.y = startPositionY;
	sprite.image.lastMove.x = 0;
	sprite.image.lastMove.y = 0;
	
	sprite.initialPosition = sprite.image.position;
	
	for (i = 0; i < 4; i++) {
		
		sprite.missile[i].image = initSprite2x1(MISSILE, ACS_BULLET, startPositionX, startPositionY);
		sprite.missile[i].name = _NULL;
	}
	
	sprite.missile[0].image.lastMove.x = 0;
	sprite.missile[0].image.lastMove.y = 1;
	
	sprite.missile[1].image.lastMove.x = 0;
	sprite.missile[1].image.lastMove.y = -1;
	
	sprite.missile[2].image.lastMove.x = 2;
	sprite.missile[2].image.lastMove.y = 0;
	
	sprite.missile[3].image.lastMove.x = -2;
	sprite.missile[3].image.lastMove.y = 0;
	
	sprite.name = _NULL;
	
	init_pair(name, fgColor, bgColor);
	
	return sprite;
}

Sprite2x1 initSprite2x1 (unsigned int name, chtype charEyes, int startPositionX, int startPositionY) {
	
	Sprite2x1 sprite;
	
	sprite.name = name;
	sprite.colorPair = name;
	sprite.charEyes = charEyes;
	sprite.position.x = startPositionX;
	sprite.position.y = startPositionY;
	sprite.lastMove.x = 0;
	sprite.lastMove.y = 0;
	
	return sprite;
}

void resetSprite (Sprite* sprite, chtype charEyes) {

	sprite->image.charEyes = charEyes;
	sprite->image.colorPair = sprite->image.name;
	sprite->image.position = sprite->initialPosition;
}

void resetMissiles (Sprite* sprite) {

	sprite->missile[0].image.position = sprite->image.position;
	sprite->missile[1].image.position = sprite->image.position;
	sprite->missile[2].image.position = sprite->image.position;
	sprite->missile[3].image.position = sprite->image.position;
}

void drawSprite (Sprite2x1* sprite) {
		
	attron(COLOR_PAIR(sprite->colorPair));
		
	mvaddch(sprite->position.y, sprite->position.x, sprite->charEyes);
	mvaddch(sprite->position.y, sprite->position.x + 1, sprite->charEyes);
		
	attroff(COLOR_PAIR(sprite->colorPair));
}

void drawSpriteInLabyrinth (Sprite2x1* sprite, Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS]) {

	drawSprite(sprite);
	
	labyrinth[sprite->position.y - LABYRINTH_Y][sprite->position.x].sprite = sprite;
}

void modifyColor (Sprite2x1* sprite, unsigned int colorPair) {
	
	sprite->colorPair = colorPair;
}

void modifySprite (Sprite2x1* sprite, unsigned int colorPair, char charEyes) {

	modifyColor(sprite, colorPair);
	sprite->charEyes = charEyes;
}

void setSprite2x1PositionFromLastMove (Sprite2x1* sprite) {
	
	if ((sprite->position.x + sprite->lastMove.x) == -2) {
		
		sprite->position.x = LABYRINTH_COLS - 2;
	}
	
	else if ((sprite->position.x+ sprite->lastMove.x) == LABYRINTH_COLS) {
		
		sprite->position.x = 0;
	}
	
	else {
		
		if (sprite->lastMove.x != 0) {
			
			sprite->position.x += sprite->lastMove.x;
		}
		
		else {
			
			sprite->position.y += sprite->lastMove.y;
		}
	}
}

void setSpritePositionFromLastMove (Sprite* sprite) {
	
	int i;
	
	setSprite2x1PositionFromLastMove (&sprite->image);
	
	for (i = 0; i < 4; i++) {
		
		if (sprite->missile[i].name == _NULL) {
			
			sprite->missile[i].image.position = sprite->image.position;
		}
	}
}

bool canMove (Point* startPosition, Point* deltaPosition, Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS]) {
	
	Point pointA = {21, (13 + LABYRINTH_Y)};
	Point pointB = {36 ,(17 + LABYRINTH_Y)};
	
	Point finalPosition;
	finalPosition.x = startPosition->x + deltaPosition->x;
	finalPosition.y = startPosition->y + deltaPosition->y;
	
	if ((startPosition->x + deltaPosition->x) < 0 || (startPosition->x + deltaPosition->x) == LABYRINTH_COLS ||
		labyrinth[(startPosition->y + deltaPosition->y - LABYRINTH_Y)][(startPosition->x + deltaPosition->x)].element != LABYRINTH_WALL) {
		
		if (!pointIntersectsRect(startPosition, &pointA, &pointB)) {
			
			if (pointIntersectsRect(&finalPosition, &pointA, &pointB)) {
				
				return FALSE;
			}
			
			else {
				
				return TRUE;
			}
		}
		
		else {
			
			return TRUE;
		}
	}
	
	else {
		
		return FALSE;
	}
}

void eraseSprite (Point position, Layer labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS]) {
    
    labyrinth[(position.y - LABYRINTH_Y)][position.x].missile = NULL;
    labyrinth[(position.y - LABYRINTH_Y)][position.x].sprite = NULL;
        
    addCharToPosition(&position, labyrinth[position.y - LABYRINTH_Y][position.x].element);
    position.x++;
    addCharToPosition(&position, labyrinth[position.y - LABYRINTH_Y][position.x].element);
}

void inverseDirectionForSprite (Sprite2x1 *sprite) {
	
	if (sprite->lastMove.x != 0) {
		
		sprite->lastMove.x *= -1;
	}
	
	else if (sprite->lastMove.y != 0) {
		
		sprite->lastMove.y *= -1;
	}
}
