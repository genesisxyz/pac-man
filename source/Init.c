/*
 *  Init.c
 *  Pac-Man Remake
 *
 *  Created by Damiano Collu on 11/07/11.
 *  Copyright 2011 Università Cagliari Informatica. All rights reserved.
 *
 */

#include "Init.h"

void initColors(void) {
	
	init_pair(DEFAULT_COLOR, COLOR_WHITE, COLOR_BLACK);
	init_pair(LABYRINTH_WALL, COLOR_BLUE, COLOR_BLACK);
	init_pair(GHOST_GATE, COLOR_YELLOW, COLOR_BLACK);
	init_pair(PILL, COLOR_YELLOW, COLOR_BLACK);
	init_pair(POWER_PILL, COLOR_YELLOW, COLOR_BLACK);
	init_pair(READY_LABEL, COLOR_YELLOW, COLOR_BLACK);
    init_pair(GAMEOVER_LABEL, COLOR_RED, COLOR_BLACK);
	init_pair(START_LABEL, COLOR_YELLOW, COLOR_BLACK);
	init_pair(PLAYERS_LABEL, COLOR_CYAN, COLOR_BLACK);
	init_pair(BONUS_LABEL, COLOR_WHITE, COLOR_BLACK);
	init_pair(COPYRIGHT_LABEL, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(LABYRINTH_WALL_WIN, COLOR_WHITE, COLOR_BLACK);
	init_pair(BLUE_GHOST, COLOR_WHITE, COLOR_BLUE);
	init_pair(BLUE_GHOST_BLINK, COLOR_BLACK, COLOR_WHITE);
	init_pair(MISSILE, COLOR_GREEN, COLOR_BLACK);
}
