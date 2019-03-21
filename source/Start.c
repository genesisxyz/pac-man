/*
 *  Start.c
 *  Pac-Man Remake
 *
 *  Created by Damiano Collu on 11/07/11.
 *  Copyright 2011 Università Cagliari Informatica. All rights reserved.
 *
 */

#include "Start.h"

void pressStartButton (unsigned int* highscore, unsigned int* points) {
	
	attron(A_BOLD);
	attron(COLOR_PAIR(DEFAULT_COLOR));
	
	mvprintw(0, 0, "\t1UP");
	
	if (*points > 0) {
		
		mvprintw(1, (int)(strlen("1UP") - digits(*points) + 1), "\t%d", *points);
	}
	
	mvprintw(0, (WINDOW_HALF_SIZE_X - (strlen("HIGH SCORE") / 2)), "HIGH SCORE");
	
	if (*highscore > 0) {
		
		mvprintw(1, (WINDOW_HALF_SIZE_X - digits(*highscore) + 1), "%d", *highscore);
	}
	mvprintw(0, (LABYRINTH_COLS - TAB_SIZE - strlen("2UP")), "2UP");
	attroff(COLOR_PAIR(DEFAULT_COLOR));
	
	attron(COLOR_PAIR(START_LABEL));
	mvprintw(WINDOW_HALF_SIZE_Y, (WINDOW_HALF_SIZE_X - (strlen("PRESS START BUTTON") / 2)), "PRESS START BUTTON");
	attroff(COLOR_PAIR(START_LABEL));
	
	attron(COLOR_PAIR(PLAYERS_LABEL));
	mvprintw((WINDOW_HALF_SIZE_Y + 3), (WINDOW_HALF_SIZE_X - (strlen("1 PLAYER ONLY") / 2)), "1 PLAYER ONLY");
	attroff(COLOR_PAIR(PLAYERS_LABEL));
	
	attron(COLOR_PAIR(BONUS_LABEL));
	mvprintw((WINDOW_HALF_SIZE_Y + 6), (WINDOW_HALF_SIZE_X - (strlen("BONUS PAC-MAN FOR 10000") / 2)), "BONUS PAC-MAN FOR 10000");
	attroff(A_BOLD);
	mvprintw((WINDOW_HALF_SIZE_Y + 6), (WINDOW_HALF_SIZE_X + (strlen("BONUS PAC-MAN FOR 10000") / 2) + 1), " PTS");
	attroff(COLOR_PAIR(BONUS_LABEL));
	
	attron(A_BOLD);
	attron(COLOR_PAIR(COPYRIGHT_LABEL));
	mvprintw((WINDOW_HALF_SIZE_Y + 9), (WINDOW_HALF_SIZE_X - (strlen("Copyright 1980 MIDWAY MFG. CO.") / 2)), "Copyright 1980 MIDWAY MFG. CO.");
	attroff(COLOR_PAIR(COPYRIGHT_LABEL));
	
	attron(COLOR_PAIR(DEFAULT_COLOR));
	mvprintw(WINDOW_SIZE_Y, 0, "\tCREDIT   99");
	attroff(COLOR_PAIR(DEFAULT_COLOR));
	attroff(A_BOLD);
	
	refresh();
	
	getch();
	
	/*
	 cancella points
    */
	mvprintw(1, 0, "\t  00", *points);
	
	/* cancella 2UP da in alto a destra */
	mvprintw(0, (WINDOW_SIZE_X - TAB_SIZE - strlen("2UP")), "   ");
}

void ready(void) {
	
	attron(A_BOLD);
	attron(COLOR_PAIR(READY_LABEL));
	mvprintw(READY_LABEL_POSITION, "READY!");
	attroff(COLOR_PAIR(READY_LABEL));
	attroff(A_BOLD);
	
	refresh();
	
	usleep(2500000);
	
	mvprintw((18 + LABYRINTH_Y), 27, "      ");
	
	refresh();
}

void gameover(void) {

    attron(A_BOLD);
	attron(COLOR_PAIR(GAMEOVER_LABEL));
	mvprintw(GAMEOVER_LABEL_POSITION, "GAME OVER");
	attroff(COLOR_PAIR(GAMEOVER_LABEL));
	attroff(A_BOLD);
	
	refresh();
}

void remainingLives (Sprite* pacman, unsigned int *lifes) {
    
    unsigned int i;
    
    move(WINDOW_SIZE_Y, 0);
    clrtoeol();
    
    for (i = 0; i < (*lifes - 1); i++) {
        
        attron(COLOR_PAIR(pacman->image.colorPair));
        mvaddch(WINDOW_SIZE_Y, (TABSIZE + (i * 3)), pacman->image.charEyes);
        mvaddch(WINDOW_SIZE_Y, (TABSIZE + (i * 3) + 1), pacman->image.charEyes);
        attroff(COLOR_PAIR(pacman->image.colorPair));
        
    }
}

void drawAllInitialPacmanLifes (Sprite* pacman, unsigned int *lifes) {

    unsigned int i;
    
    move(WINDOW_SIZE_Y, 0);
    clrtoeol();
    
    for (i = 0; i < *lifes; i++) {
        
        attron(COLOR_PAIR(pacman->image.colorPair));
        mvaddch(WINDOW_SIZE_Y, (TABSIZE + (i * 3)), pacman->image.charEyes);
        mvaddch(WINDOW_SIZE_Y, (TABSIZE + (i * 3) + 1), pacman->image.charEyes);
        attroff(COLOR_PAIR(pacman->image.colorPair));
        
    }
}
