/*
 *  LabelPlayer1.c
 *  Pac-Man Remake
 *
 *  Created by Damiano Collu on 11/07/11.
 *  Copyright 2011 Università Cagliari Informatica. All rights reserved.
 *
 */

#include "LabelPlayer1.h"

void player1LabelBlinking (unsigned int* schedule) {

	/* lampeggia ogni 0.5 secondi */	
	if (*schedule == (REFRESH * FAKE_FPS * 0.5)) {
		
		attron(A_BOLD);
		attron(COLOR_PAIR(DEFAULT_COLOR));
		mvprintw(0, 0, "\t   ");
		attroff(COLOR_PAIR(DEFAULT_COLOR));
		attroff(A_BOLD);
		
		*schedule += REFRESH;
	}
	
	else if (*schedule == (REFRESH * FAKE_FPS)) {
		
		attron(A_BOLD);
		attron(COLOR_PAIR(DEFAULT_COLOR));
		mvprintw(0, 0, "\t1UP");
		attroff(COLOR_PAIR(DEFAULT_COLOR));
		attroff(A_BOLD);
		
		*schedule = 0;
	}
	
	else {
		
		*schedule += REFRESH;
	}
}
