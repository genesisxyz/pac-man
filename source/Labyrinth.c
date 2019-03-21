/*
 *  Labyrinth.c
 *  Pac-Man Remake
 *
 *  Created by Damiano Collu on 25/06/11.
 *  Copyright 2011 Università Cagliari Informatica. All rights reserved.
 *
 */

#include "Labyrinth.h"

void initLabyrinth (char labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], Layer tempLabyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], Sprite* pacman, Sprite ghost[GHOSTS_NUMBER], Pills* pills) {
	
	int row, col;
	
	pills->value = 0;
	
	for (row = 0; row < LABYRINTH_ROWS; row++) {
		
		for (col = 0; col < LABYRINTH_COLS; col++) {
			
			switch (labyrinth[row][col]) {
				case '|':
					attron(COLOR_PAIR(LABYRINTH_WALL));
					mvaddch((row + LABYRINTH_Y), col, ACS_VLINE);
					attroff(COLOR_PAIR(LABYRINTH_WALL));
					tempLabyrinth[row][col].element = LABYRINTH_WALL;
					tempLabyrinth[row][col].sprite = NULL;
					tempLabyrinth[row][col].missile = NULL;
					break;
				case '-':
					attron(COLOR_PAIR(LABYRINTH_WALL));
					mvaddch((row + LABYRINTH_Y), col, ACS_HLINE);
					attroff(COLOR_PAIR(LABYRINTH_WALL));
					tempLabyrinth[row][col].element = LABYRINTH_WALL;
					tempLabyrinth[row][col].sprite = NULL;
					tempLabyrinth[row][col].missile = NULL;
					break;
				case '[':
					attron(COLOR_PAIR(LABYRINTH_WALL));
					mvaddch((row + LABYRINTH_Y), col, ACS_ULCORNER);
					attroff(COLOR_PAIR(LABYRINTH_WALL));
					tempLabyrinth[row][col].element = LABYRINTH_WALL;
					tempLabyrinth[row][col].sprite = NULL;
					tempLabyrinth[row][col].missile = NULL;
					break;
				case ']':
					attron(COLOR_PAIR(LABYRINTH_WALL));
					mvaddch((row + LABYRINTH_Y), col, ACS_URCORNER);
					attroff(COLOR_PAIR(LABYRINTH_WALL));
					tempLabyrinth[row][col].element = LABYRINTH_WALL;
					tempLabyrinth[row][col].sprite = NULL;
					tempLabyrinth[row][col].missile = NULL;
					break;
				case '(':
					attron(COLOR_PAIR(LABYRINTH_WALL));
					mvaddch((row + LABYRINTH_Y), col, ACS_LLCORNER);
					attroff(COLOR_PAIR(LABYRINTH_WALL));
					tempLabyrinth[row][col].element = LABYRINTH_WALL;
					tempLabyrinth[row][col].sprite = NULL;
					tempLabyrinth[row][col].missile = NULL;
					break;
				case ')':
					attron(COLOR_PAIR(LABYRINTH_WALL));
					mvaddch((row + LABYRINTH_Y), col, ACS_LRCORNER);
					attroff(COLOR_PAIR(LABYRINTH_WALL));
					tempLabyrinth[row][col].element = LABYRINTH_WALL;
					tempLabyrinth[row][col].sprite = NULL;
					tempLabyrinth[row][col].missile = NULL;
					break;
				case '+':
					attron(COLOR_PAIR(LABYRINTH_WALL));
					mvaddch((row + LABYRINTH_Y), col, ' ');
					attroff(COLOR_PAIR(LABYRINTH_WALL));
					tempLabyrinth[row][col].element = LABYRINTH_WALL;
					tempLabyrinth[row][col].sprite = NULL;
					tempLabyrinth[row][col].missile = NULL;
					break;
				case '.':
					attron(COLOR_PAIR(PILL));
					mvaddch((row + LABYRINTH_Y), col, ACS_BULLET);
					attroff(COLOR_PAIR(PILL));
					tempLabyrinth[row][col].element = PILL;
					tempLabyrinth[row][col].sprite = NULL;
					tempLabyrinth[row][col].missile = NULL;
					pills->value++;
					break;
				case '0':
					attron(A_BOLD);
					attron(COLOR_PAIR(POWER_PILL));
					mvaddch((row + LABYRINTH_Y), col, '0');
					attroff(COLOR_PAIR(POWER_PILL));
					attroff(A_BOLD);
					tempLabyrinth[row][col].element = POWER_PILL;
					tempLabyrinth[row][col].sprite = NULL;
					tempLabyrinth[row][col].missile = NULL;
					pills->value++;
					break;
				case '_':
					attron(COLOR_PAIR(GHOST_GATE));
					mvaddch((row + LABYRINTH_Y), col, '_');
					attroff(COLOR_PAIR(GHOST_GATE));
					tempLabyrinth[row][col].element = GHOST_GATE;
					tempLabyrinth[row][col].sprite = NULL;
					tempLabyrinth[row][col].missile = NULL;
					break;
				case 'I':
					attron(COLOR_PAIR(GHOST_GATE));
					mvaddch((row + LABYRINTH_Y), col, ACS_VLINE);
					attroff(COLOR_PAIR(GHOST_GATE));
					tempLabyrinth[row][col].element = GHOST_DOOR;
					tempLabyrinth[row][col].sprite = NULL;
					tempLabyrinth[row][col].missile = NULL;
					break;
				case 'P':
					*pacman = initSprite(PACMAN, COLOR_YELLOW, COLOR_WHITE, '.', col, (row + LABYRINTH_Y));
					pacman->image.lastMove.x = -2;
					pacman->image.lastMove.y = 0;
					tempLabyrinth[row][col].element = EMPTY;
					tempLabyrinth[row][col].sprite = &pacman->image;
					tempLabyrinth[row][col].missile = NULL;
					break;
				case '1':
					ghost[0] = initSprite(RED_GHOST, COLOR_RED, COLOR_BLUE, '-', col - 1, (row + LABYRINTH_Y));
					ghost[0].image.lastMove.x = 0;
					ghost[0].image.lastMove.y = -1;
					tempLabyrinth[row][col].element = EMPTY;
					tempLabyrinth[row][col].missile = NULL;
					tempLabyrinth[row][col].sprite = NULL;
					ghost[4] = initSprite(RED_GHOST_, COLOR_RED, COLOR_BLUE, '-', col - 1, (row + LABYRINTH_Y));
					ghost[4].image.lastMove.x = 0;
					ghost[4].image.lastMove.y = -1;
					attron(COLOR_PAIR(DEFAULT_COLOR));
					mvaddch((row + LABYRINTH_Y), col, ' ');
					attroff(COLOR_PAIR(DEFAULT_COLOR));
					break;
				case '2':
					ghost[1] = initSprite(GREEN_GHOST, COLOR_MAGENTA, COLOR_BLUE, '-', col - 1, (row + LABYRINTH_Y));
					ghost[1].image.lastMove.x = 0;
					ghost[1].image.lastMove.y = -1;
					tempLabyrinth[row][col].element = EMPTY;
					tempLabyrinth[row][col].missile = NULL;
					tempLabyrinth[row][col].sprite = NULL;
					ghost[5] = initSprite(GREEN_GHOST_, COLOR_MAGENTA, COLOR_BLUE, '-', col - 1, (row + LABYRINTH_Y));
					ghost[5].image.lastMove.x = 0;
					ghost[5].image.lastMove.y = -1;
					attron(COLOR_PAIR(DEFAULT_COLOR));
					mvaddch((row + LABYRINTH_Y), col, ' ');
					attroff(COLOR_PAIR(DEFAULT_COLOR));
					break;
				case '3':
					ghost[2] = initSprite(CYAN_GHOST, COLOR_CYAN, COLOR_BLUE, '-', col - 1, (row + LABYRINTH_Y));
					ghost[2].image.lastMove.x = 0;
					ghost[2].image.lastMove.y = -1;
					tempLabyrinth[row][col].element = EMPTY;
					tempLabyrinth[row][col].missile = NULL;
					tempLabyrinth[row][col].sprite = NULL;
					ghost[6] = initSprite(CYAN_GHOST_, COLOR_CYAN, COLOR_BLUE, '-', col - 1, (row + LABYRINTH_Y));
					ghost[6].image.lastMove.x = 0;
					ghost[6].image.lastMove.y = -1;
					attron(COLOR_PAIR(DEFAULT_COLOR));
					mvaddch((row + LABYRINTH_Y), col, ' ');
					attroff(COLOR_PAIR(DEFAULT_COLOR));
					break;
				case '4':
					ghost[3] = initSprite(WHITE_GHOST, COLOR_WHITE, COLOR_BLUE, '-', col - 1, (row + LABYRINTH_Y));
					ghost[3].image.lastMove.x = 0;
					ghost[3].image.lastMove.y = -1;
					tempLabyrinth[row][col].element = EMPTY;
					tempLabyrinth[row][col].missile = NULL;
					tempLabyrinth[row][col].sprite = NULL;
					ghost[7] = initSprite(WHITE_GHOST_, COLOR_WHITE, COLOR_BLUE, '-', col - 1, (row + LABYRINTH_Y));
					ghost[7].image.lastMove.x = 0;
					ghost[7].image.lastMove.y = -1;
					attron(COLOR_PAIR(DEFAULT_COLOR));
					mvaddch((row + LABYRINTH_Y), col, ' ');
					attroff(COLOR_PAIR(DEFAULT_COLOR));
					break;
				default:
					attron(COLOR_PAIR(DEFAULT_COLOR));
					mvaddch((row + LABYRINTH_Y), col, ' ');
					attroff(COLOR_PAIR(DEFAULT_COLOR));
					tempLabyrinth[row][col].element = EMPTY;
					tempLabyrinth[row][col].sprite = NULL;
					tempLabyrinth[row][col].missile = NULL;
					break;
			}
		}
	}
	
	pills->initialValue = pills->value;
	
	ghostHideUnderPill(ghost, tempLabyrinth);
	
	drawSprite(&pacman->image);
}

void resetPillsInLabyrinth (char labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], Layer tempLabyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], Pills *pills) {

	int row, col;
	
	for (row = 0; row < LABYRINTH_ROWS; row++) {
		
		for (col = 0; col < LABYRINTH_COLS; col++) {
		
			switch (labyrinth[row][col]) {
				
				case '.':
					attron(COLOR_PAIR(PILL));
					mvaddch((row + LABYRINTH_Y), col, ACS_BULLET);
					attroff(COLOR_PAIR(PILL));
					tempLabyrinth[row][col].element = PILL;
					break;
				case '0':
					attron(A_BOLD);
					attron(COLOR_PAIR(POWER_PILL));
					mvaddch((row + LABYRINTH_Y), col, '0');
					attroff(COLOR_PAIR(POWER_PILL));
					attroff(A_BOLD);
					tempLabyrinth[row][col].element = POWER_PILL;
					break;
				case '_':
					attron(COLOR_PAIR(GHOST_GATE));
					mvaddch((row + LABYRINTH_Y), col, '_');
					attroff(COLOR_PAIR(GHOST_GATE));
					break;
				case 'I':
					attron(COLOR_PAIR(GHOST_GATE));
					mvaddch((row + LABYRINTH_Y), col, ACS_VLINE);
					attroff(COLOR_PAIR(GHOST_GATE));
					break;
			}
		}
	}
	
	pills->value = pills->initialValue;
}

void resetLabyrinth (char labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], Layer tempLabyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], Pills *pills) {

	int row, col;
	
	for (row = 0; row < LABYRINTH_ROWS; row++) {
		
		for (col = 0; col < LABYRINTH_COLS; col++) {
			
			switch (labyrinth[row][col]) {
					
				case '|':
					attron(COLOR_PAIR(LABYRINTH_WALL));
					mvaddch((row + LABYRINTH_Y), col, ACS_VLINE);
					attroff(COLOR_PAIR(LABYRINTH_WALL));
					tempLabyrinth[row][col].element = LABYRINTH_WALL;
					break;
				case '-':
					attron(COLOR_PAIR(LABYRINTH_WALL));
					mvaddch((row + LABYRINTH_Y), col, ACS_HLINE);
					attroff(COLOR_PAIR(LABYRINTH_WALL));
					tempLabyrinth[row][col].element = LABYRINTH_WALL;
					break;
				case '[':
					attron(COLOR_PAIR(LABYRINTH_WALL));
					mvaddch((row + LABYRINTH_Y), col, ACS_ULCORNER);
					attroff(COLOR_PAIR(LABYRINTH_WALL));
					tempLabyrinth[row][col].element = LABYRINTH_WALL;
					break;
				case ']':
					attron(COLOR_PAIR(LABYRINTH_WALL));
					mvaddch((row + LABYRINTH_Y), col, ACS_URCORNER);
					attroff(COLOR_PAIR(LABYRINTH_WALL));
					tempLabyrinth[row][col].element = LABYRINTH_WALL;
					break;
				case '(':
					attron(COLOR_PAIR(LABYRINTH_WALL));
					mvaddch((row + LABYRINTH_Y), col, ACS_LLCORNER);
					attroff(COLOR_PAIR(LABYRINTH_WALL));
					tempLabyrinth[row][col].element = LABYRINTH_WALL;
					break;
				case ')':
					attron(COLOR_PAIR(LABYRINTH_WALL));
					mvaddch((row + LABYRINTH_Y), col, ACS_LRCORNER);
					attroff(COLOR_PAIR(LABYRINTH_WALL));
					tempLabyrinth[row][col].element = LABYRINTH_WALL;
					break;
				case '+':
					attron(COLOR_PAIR(LABYRINTH_WALL));
					mvaddch((row + LABYRINTH_Y), col, ' ');
					attroff(COLOR_PAIR(LABYRINTH_WALL));
					tempLabyrinth[row][col].element = LABYRINTH_WALL;
					break;
				case '.':
					attron(COLOR_PAIR(PILL));
					mvaddch((row + LABYRINTH_Y), col, ACS_BULLET);
					attroff(COLOR_PAIR(PILL));
					tempLabyrinth[row][col].element = PILL;
					pills->value++;
					break;
				case '0':
					attron(A_BOLD);
					attron(COLOR_PAIR(POWER_PILL));
					mvaddch((row + LABYRINTH_Y), col, '0');
					attroff(COLOR_PAIR(POWER_PILL));
					attroff(A_BOLD);
					tempLabyrinth[row][col].element = POWER_PILL;
					pills->value++;
					break;
				case '_':
					attron(COLOR_PAIR(GHOST_GATE));
					mvaddch((row + LABYRINTH_Y), col, '_');
					attroff(COLOR_PAIR(GHOST_GATE));
					tempLabyrinth[row][col].element = GHOST_GATE;
					break;
				case 'I':
					attron(COLOR_PAIR(GHOST_GATE));
					mvaddch((row + LABYRINTH_Y), col, ACS_VLINE);
					attroff(COLOR_PAIR(GHOST_GATE));
					tempLabyrinth[row][col].element = GHOST_DOOR;
					break;
				default:
					attron(COLOR_PAIR(DEFAULT_COLOR));
					mvaddch((row + LABYRINTH_Y), col, ' ');
					attroff(COLOR_PAIR(DEFAULT_COLOR));
					tempLabyrinth[row][col].element = EMPTY;
					break;
			}
		}
	}
	
	pills->value = pills->initialValue;
}

void addCharToPosition (Point* position, chtype symbol) {
	
	switch (symbol) {
		case PILL:
			attron(COLOR_PAIR(PILL));
			mvaddch(position->y,position->x, ACS_BULLET);
			attroff(COLOR_PAIR(PILL));
			break;
		case POWER_PILL:
			attron(A_BOLD);
			attron(COLOR_PAIR(POWER_PILL));
			mvaddch(position->y,position->x, '0');
			attroff(COLOR_PAIR(POWER_PILL));
			attroff(A_BOLD);
			break;
		case GHOST_GATE:
			attron(COLOR_PAIR(GHOST_GATE));
			mvaddch(position->y,position->x, '_');
			attroff(COLOR_PAIR(GHOST_GATE));
			break;
		case GHOST_DOOR:
			attron(COLOR_PAIR(GHOST_GATE));
			mvaddch(position->y,position->x, ACS_VLINE);
			attroff(COLOR_PAIR(GHOST_GATE));
			break;
		default:
			attron(COLOR_PAIR(DEFAULT_COLOR));
			mvaddch(position->y, position->x, ' ');
			attroff(COLOR_PAIR(DEFAULT_COLOR));
			break;
	}
}

void resetSpritesPositions (Layer tempLabyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], Sprite* pacman, Sprite ghost[GHOSTS_NUMBER]) {
	
	int i, k;
	
	/* reimposta fantasmi */
	for (i = 0; i < GHOSTS_NUMBER; i++) {
		
		eraseSprite(ghost[i].image.position, tempLabyrinth);
		resetSprite(&ghost[i], '-');
		ghost[i].image.lastMove.x = 0;
		ghost[i].image.lastMove.y = -1;
		
		for (k = 0; k < 4; k++) {
			
			/* reimposta missili del fantasma */
			if (ghost[i].missile[k].name != _NULL) {
				
				eraseSprite(ghost[i].missile[k].image.position, tempLabyrinth);
				
				ghost[i].missile[k].image.position = ghost[i].image.position;
				ghost[i].missile[k].name = _NULL;
			}
		}
	}
	
	/* reimposta Pac-Man */
	eraseSprite(pacman->image.position, tempLabyrinth);
	resetSprite(pacman, '.');
	pacman->image.lastMove.x = -2;
	pacman->image.lastMove.y = 0;
	
	for (k = 0; k < 4; k++) {
		
		/* reimposta missili di Pac-Man */
		if (pacman->missile[k].name != _NULL) {
		
			eraseSprite(pacman->missile[k].image.position, tempLabyrinth);
			
			pacman->missile[k].image.position = pacman->image.position;
			pacman->missile[k].name = _NULL;
		}
	}
	
	drawSpriteInLabyrinth(&pacman->image, tempLabyrinth);
}

void labyrinthBlinking (char labyrinth[LABYRINTH_ROWS][LABYRINTH_COLS], Sprite ghost[GHOSTS_NUMBER]) {
	
	unsigned int blinkingTimes = LABYRINTH_WALL_WIN_TIMES;
	unsigned int colorSteps = 0; /* alterna i colori */
	
	unsigned int row;
	unsigned int col;
	
	/* cancella i fantasmi dalla schermata di gioco */
	for (col = 0; col < GHOSTS_NUMBER; col++) {
		
		mvprintw(ghost[col].image.position.y, ghost[col].image.position.x, "  ");
	}
	
	do {
		
		colorSteps = (colorSteps + 1) % 2;
		
		if (colorSteps == 0) {
			
			attron(COLOR_PAIR(LABYRINTH_WALL));
		}
		
		else {
			
			attron(COLOR_PAIR(LABYRINTH_WALL_WIN));
		}
		
		for (row = 0; row < LABYRINTH_ROWS; row++) {
			
			for (col = 0; col < LABYRINTH_COLS; col++) {
				
				switch (labyrinth[row][col]) {
					case '|':
						mvaddch((row + LABYRINTH_Y), col, ACS_VLINE);
						break;
					case '-':
						mvaddch((row + LABYRINTH_Y), col, ACS_HLINE);
						break;
					case '[':
						mvaddch((row + LABYRINTH_Y), col, ACS_ULCORNER);
						break;
					case ']':
						mvaddch((row + LABYRINTH_Y), col, ACS_URCORNER);
						break;
					case '(':
						mvaddch((row + LABYRINTH_Y), col, ACS_LLCORNER);
						break;
					case ')':
						mvaddch((row + LABYRINTH_Y), col, ACS_LRCORNER);
						break;
					case 'I':
					case '_':
						mvaddch((row + LABYRINTH_Y), col, ' ');
						break;
				}
			}
		}
		
		if (colorSteps == 0) {
			
			attroff(COLOR_PAIR(LABYRINTH_WALL));
			
			/* sottraento le volte che deve lampeggiare qui si fermerà quanto il labirinto è del colore normale */
			blinkingTimes--;
		}
		
		else {
			
			attroff(COLOR_PAIR(LABYRINTH_WALL_WIN));
		}
		
		refresh();
		
		usleep(LABYRINTH_WALL_BLINK);
		
	} while (blinkingTimes > 0);
}
